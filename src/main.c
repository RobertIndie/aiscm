#include <reg52.h>

#define HEAP_MEMORY_SIZE 128
#define USE_LARGE false         // 是否使用Large 模式编译
#define USE_IDATA_IN_HEAP true  // 堆内存是否存在idata区中

typedef unsigned char uchar;
typedef unsigned char u16;

// IO层
void ReadNByte(uchar* dat, u16 n) {
  uchar i;
  for (i = 0; i < n; i++) {
    dat[i] = SBUF;
    while (!RI)
      ;
    RI = 0;
  }
}

void ReadNFloat(float* dat, u16 n) {
  uchar* ptr = dat;
  ReadNByte(ptr, sizeof(float) * n);
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
struct EVALUATE_ACK {
  float* output_data;  // 长度固定为输出成神经元个数
};

#define ERROR_ID 8
struct ERROR {
  uchar error_type;
};
#define ERROR_ERR_CMD_TYPE 1
#define ERROR_ERR_PARAM 2
#define ERROR_ERR_LACK_OF_MEM 3
#define ERROR_ERR_NET_NOT_INIT 4

union COMMAND {  // 利用共用体优化RAM空间占用
  struct SET_STRUCT set_struct;
  struct SET_WEIGHTS set_weights;
  struct EVALUATE evaluate;
  struct EVALUATE_ACK evaluate_ack;
  struct ERROR error;
};

// 维护的全局变量：
uchar layer_count;  //层数 一定要大于等于2
uchar* neurons_count_list;  //每层的神经元个数，指向的内存落在heap_memory中
float* weight_matrix;  //权值矩阵，指向的内存落在heap_memory中
unsigned short weight_matrix_len;
unsigned short used_mem;  // heap_memory使用的内存
#if USE_IDATA_IN_HEAP
idata
#endif
    uchar heap_memory[HEAP_MEMORY_SIZE];

uchar NewMem(uchar* ptr, uchar count) {
  if (used_mem + count > HEAP_MEMORY_SIZE)
    return ERROR_ERR_LACK_OF_MEM;  //堆内存不足
  ptr = &heap_memory[used_mem];
  used_mem += count;
  return 0;
}

uchar CopyMem(uchar* src_ptr, uchar* dest_ptr, uchar len) {
  uchar i;
  for (i = 0; i < len; i++) {
    dest_ptr[i] = src_ptr[i];
  }
  return 0;
}

void ComputeWeightMatrixLen() {
  uchar i;
  weight_matrix_len = 0;
  for (i = 1; i < layer_count; i++) {
    weight_matrix_len +=
        (neurons_count_list[i - 1] + 1) * neurons_count_list[i];
  }
}

uchar set_struct(struct SET_STRUCT* param);
uchar set_weights(struct SET_WEIGHTS* param, u16 weights_count);

void ReadPacket() {
  uchar type_id;
  union COMMAND cmd;
  union COMMAND out_cmd;
  uchar err;
  while (1) {
    ReadNByte(&type_id, sizeof(type_id));
    switch (type_id) {
      case PING_ID:
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        break;
      case SET_STRUCT_ID:
        ReadNByte(&cmd.set_struct.layer_count,
                  sizeof(cmd.set_struct.layer_count));
        ReadNByte(cmd.set_struct.layers, cmd.set_struct.layer_count);
        err = set_struct(&cmd.set_struct);
        if (err != 0) {
          type_id = ERROR_ID;
          WriteNByte(&type_id, sizeof(type_id));
          cmd.error.error_type = err;
          WriteNByte(&cmd.error.error_type, sizeof(cmd.error.error_type));
        }
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        break;
      case SET_WEIGHTS_ID:
        ReadNByte(&cmd.set_weights.layer_id, sizeof(cmd.set_weights.layer_id));
        ReadNFloat(cmd.set_weights.weights,
                   (neurons_count_list[cmd.set_weights.layer_id - 1] + 1) *
                       neurons_count_list[cmd.set_weights.layer_id]);
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        break;
      case EVALUATE_ID:
        ReadNFloat(cmd.evaluate.input_data, neurons_count_list[0]);
        type_id++;
        // TODO
        break;
    }
  }
}

// 运算层

uchar set_struct(struct SET_STRUCT* param) {
  uchar err;
  if (param->layer_count < 2) return ERROR_ERR_PARAM;
  layer_count = param->layer_count;
  err = NewMem(neurons_count_list, layer_count);
  if (err != 0) return err;  // 透传错误码
  CopyMem(neurons_count_list, param->layers, layer_count);
  ComputeWeightMatrixLen();
}

uchar set_weights(
    struct SET_WEIGHTS* param,
    u16 weights_count) {  //直接传入计算好的权重个数，不需要内部重新计算
  if (neurons_count_list == 0) return ERROR_ERR_NET_NOT_INIT;
  if (param->layer_id >= layer_count) return ERROR_ERR_PARAM;
}

int main() {}
