#include <reg52.h>

#define WORKING_MODE 1  // 0为动态模式，1为静态模式
#define HEAP_MEMORY_SIZE 1
#define USER_HEAP_MEM_SIZE 25
#define USE_LARGE 1          // 是否使用Large 模式编译
#define USE_IDATA_IN_HEAP 1  // 堆内存是否存在idata区中
#define SIGMOID_OPTIMIZE 3   // sigmoid优化模式
#if SIGMOID_OPTIMIZE >= 1
#define SIGMOID_PRECISION 100
#endif

#define ERROR_ERR_CMD_TYPE 1
#define ERROR_ERR_PARAM 2
#define ERROR_ERR_LACK_OF_MEM 3
#define ERROR_ERR_NET_NOT_INIT 4

typedef unsigned char uchar;
typedef unsigned char u16;

// 内存管理
// 维护的全局变量：
#if WORKING_MODE == 0
uchar layer_count;  //层数 一定要大于等于2
uchar* neurons_count_list;  //每层的神经元个数，指向的内存落在heap_memory中
float* weight_matrix;  //权值矩阵，指向的内存落在heap_memory中
u16 weight_matrix_len;
float*
    evaluate_tmp_mem;  // 用于运算的临时内存，其长度为neurons_count_list最大元素的值
uchar evaluate_tmp_mem_len;  // 运算临时内存的长度
#elif WORKING_MODE == 1
#include <static_mode.h>
#endif
u16 used_mem;  // heap_memory使用的内存
uchar user_space_mem[USER_HEAP_MEM_SIZE];
#if USE_IDATA_IN_HEAP && !USE_LARGE
idata
#endif
    uchar heap_memory[HEAP_MEMORY_SIZE];

// HeapMemory
uchar NewMem(uchar* ptr, u16 count) {
  if (used_mem + count > HEAP_MEMORY_SIZE)
    return ERROR_ERR_LACK_OF_MEM;  //堆内存不足
  ptr = &heap_memory[used_mem];
  used_mem += count;
  return 0;
}

uchar CopyMem(uchar* src_ptr, uchar* dest_ptr, u16 len) {
  u16 i;
  for (i = 0; i < len; i++) {
    dest_ptr[i] = src_ptr[i];
  }
  return 0;
}
// ===============

// IO层
void ReadNByte(uchar* dat, u16 n, uchar use_user_space) {
  uchar i;
  if (use_user_space) dat = user_space_mem;  // 将指针定位到用户区内存中
  for (i = 0; i < n; i++) {
    dat[i] = SBUF;
    while (!RI)
      ;
    RI = 0;
  }
}

void ReadNFloat(float* dat, u16 n) {
  uchar* ptr = dat;
  ReadNByte(ptr, sizeof(float) * n, 1);  // 读float数据均在用户区内存中
}

void WriteNByte(uchar* dat, u16 n) {
  uchar i;
  for (i = 0; i < n; i++) {
    SBUF = dat[i];
    while (!TI)
      ;
    TI = 0;
  }
}

void WriteNFloat(float* dat, u16 n) {
  uchar* ptr = dat;
  WriteNByte(ptr, sizeof(float) * n);
}

// 指令层

#define PING_ID 0

#define SET_STRUCT_ID 2
struct SET_STRUCT {
  uchar layer_count;  // 需要校验：大于等于2
  uchar* layers;
};

#define SET_WEIGHTS_ID 4
struct SET_WEIGHTS {
  uchar layer_id;  // 需要校验：存在layer
  float* weights;
};

#define EVALUATE_ID 6
struct EVALUATE {
  float* input_data;  // 长度固定为输入层神经元个数
};

#define EVALUATE_ACK_ID 7
struct EVALUATE_ACK {  // 这里和EVALUATE是相同结构的，故下文将不进行转换
  float* output_data;  // 长度固定为输出层神经元个数
};

#define ERROR_ID 8
struct ERROR {
  uchar error_type;
};

union COMMAND {  // 利用共用体优化RAM空间占用
  struct SET_STRUCT set_struct;
  struct SET_WEIGHTS set_weights;
  struct EVALUATE evaluate;
  struct EVALUATE_ACK evaluate_ack;
  struct ERROR error;
};

void ComputeWeightMatrixLen() {
  uchar i;
  weight_matrix_len = 0;
  for (i = 1; i < layer_count; i++) {
    weight_matrix_len +=
        (neurons_count_list[i - 1] + 1) * neurons_count_list[i];
  }
}

u16 GetLayerWeightIndex(uchar layer) {
  uchar i;
  u16 result;
  for (i = layer; i >= 1; i--) {
    result += (neurons_count_list[i - 1] + 1) * neurons_count_list[i];
  }
  return result;
}

uchar set_struct(struct SET_STRUCT* param);
uchar set_weights(struct SET_WEIGHTS* param, u16 weights_count);

#define RETURN_ERROR                                                 \
  if (err != 0) {                                                    \
    type_id = ERROR_ID;                                              \
    WriteNByte(&type_id, sizeof(type_id));                           \
    cmd.error.error_type = err;                                      \
    WriteNByte(&cmd.error.error_type, sizeof(cmd.error.error_type)); \
    break;                                                           \
  }

void ReadPacket() {
  uchar type_id;
  union COMMAND cmd;
  uchar err;
  u16 tmp;
  while (1) {
    ReadNByte(&type_id, sizeof(type_id), 0);
    switch (type_id) {
      case PING_ID:
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        break;
      case SET_STRUCT_ID:
        ReadNByte(&cmd.set_struct.layer_count,
                  sizeof(cmd.set_struct.layer_count), 0);
        ReadNByte(cmd.set_struct.layers, cmd.set_struct.layer_count, 1);
        err = set_struct(&cmd.set_struct);
        RETURN_ERROR
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        break;
      case SET_WEIGHTS_ID:
        ReadNByte(&cmd.set_weights.layer_id, sizeof(cmd.set_weights.layer_id),
                  0);
        tmp = (neurons_count_list[cmd.set_weights.layer_id - 1] + 1) *
              neurons_count_list[cmd.set_weights.layer_id];
        ReadNFloat(cmd.set_weights.weights, tmp);
        err = set_weights(&cmd.set_weights, tmp);
        RETURN_ERROR
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        break;
      case EVALUATE_ID:
        ReadNFloat(cmd.evaluate.input_data, neurons_count_list[0]);
        err = evaluate(&cmd.evaluate);
        RETURN_ERROR
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        WriteNFloat(cmd.evaluate_ack.output_data,
                    neurons_count_list[layer_count - 1]);
        break;
    }
  }
}

// 运算层

uchar set_struct(struct SET_STRUCT* param) {
  uchar err;
  uchar i;
  evaluate_tmp_mem_len = 0;
  if (param->layer_count < 2) return ERROR_ERR_PARAM;
  layer_count = param->layer_count;
  err = NewMem(neurons_count_list, layer_count);
  if (err != 0) return err;  // 透传错误码
  CopyMem(neurons_count_list, param->layers, layer_count);
  ComputeWeightMatrixLen();
  err = NewMem((uchar*)weight_matrix, weight_matrix_len);
  if (err != 0) return err;
  for (i = 0; i < layer_count; i++) {
    if (neurons_count_list[i] >= evaluate_tmp_mem_len)
      evaluate_tmp_mem_len = neurons_count_list[i];
  }
  err = NewMem((uchar*)evaluate_tmp_mem, evaluate_tmp_mem_len);
  if (err != 0) return err;
  return 0;
}

uchar set_weights(
    struct SET_WEIGHTS* param,
    u16 weights_count) {  //直接传入计算好的权重个数，不需要内部重新计算
  if (neurons_count_list == 0) return ERROR_ERR_NET_NOT_INIT;
  if (param->layer_id >= layer_count ||
      param->layer_id < 1)  //不能设置第一层输入层的权值矩阵
    return ERROR_ERR_PARAM;
  CopyMem((uchar*)(param->weights),
          (uchar*)(weight_matrix + GetLayerWeightIndex(param->layer_id)),
          weights_count);
  return 0;
}

#define START_POINT -100
#define SG_LEN 200
#if SIGMOID_OPTIMIZE >= 1
float GetSigmoid(int index) {
  if (index < 0) return 0;
  if (index > SIGMOID_PRECISION) return 1;
  return sigmoid_table[index];
}
#endif
#if SIGMOID_OPTIMIZE == 0
#include <math.h>
float sigmoid(float n) { return 1 / (1 + exp(-n)); }
#elif SIGMOID_OPTIMIZE == 1
#include "sigmoid_table.h"
float sigmoid(float n) {
  return GetSigmoid((int)(SIGMOID_PRECISION * (n - START_POINT) / SG_LEN));
}
#elif SIGMOID_OPTIMIZE == 2
#include <math.h>
#include "sigmoid_table.h"
float sigmoid(float n) {
  return (GetSigmoid((int)ceil(n)) + GetSigmoid((int)floor(n))) / 2;
}
#elif SIGMOID_OPTIMIZE == 3
#include <math.h>
#include "sigmoid_table.h"
float sigmoid(float n) {
  float tmp = SIGMOID_PRECISION * (n - START_POINT) / SG_LEN;
  int a = (int)ceil(tmp);
  float y1 = GetSigmoid(a);
  float y2 = GetSigmoid(a + 1);
  float x1 = START_POINT + a * SG_LEN / SIGMOID_PRECISION;
  float x2 = START_POINT + (a + 1) * SG_LEN / SIGMOID_PRECISION;
  return (y2 - y1) * (n - x1) / (x2 - x1) + y1;
}
#endif

uchar evaluate(struct EVALUATE* param) {
  uchar i;
  uchar j;
  uchar k;
  float* ptr = weight_matrix;
  uchar* layer_ptr = weight_matrix + GetLayerWeightIndex(1);
  float* input_data = param->input_data;
  for (i = 1; i < layer_count; i++) {
    for (j = 0; j < neurons_count_list[j]; j++) {
      evaluate_tmp_mem[j] = 0;
      for (k = 0; k < neurons_count_list[j - 1]; k++) {
        evaluate_tmp_mem[j] += input_data[j - 1] * *ptr;  // 权重
        ptr++;
      }
      evaluate_tmp_mem[j] -= *ptr;  //阈值
      evaluate_tmp_mem[j] = sigmoid(evaluate_tmp_mem[j]);
      ptr++;
    }
    CopyMem((uchar*)evaluate_tmp_mem, (uchar*)input_data,
            neurons_count_list[j]);  // 将当前层的输出作为下一层的输入
  }
  // 循环结束后，input_data已经是输出结果了
  return 0;
}

int main() {
  SCON = 0X50;  //设置为工作方式1
  TMOD = 0X20;  //设置计数器工作方式2
  PCON = 0X80;  //波特率加倍
  TH1 = 0XF3;   //计数器初始值设置，波特率4800
  TL1 = 0XF3;
  ES = 1;   //打开接收中断
  EA = 1;   //打开总中断
  TR1 = 1;  //打开计数器
  while (1)
    ;
  return 0;
}
