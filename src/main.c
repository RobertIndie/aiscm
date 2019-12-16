#include <reg52.h>

#define WORKING_MODE 1  // 0Ϊ��̬ģʽ��1Ϊ��̬ģʽ
#if WORKING_MODE == 0  // ֻ��Ϊ��̬ģʽ����ҪΪȫ��ָ�����������ڴ�
#define HEAP_MEMORY_SIZE \
  48  // ���Ե��ڶ��ڴ�ռ���û����ڴ�ռ����������RAM
#endif
#define USER_HEAP_MEM_SIZE 24
#define USE_LARGE 0          // �Ƿ�ʹ��Large ģʽ����
#define USE_IDATA_IN_HEAP 1  // ���ڴ��Ƿ����idata����
// sigmoid�Ż�ģʽ��
// 0: ֱ�ӽ���sigmoid����
// 1: ֱ�Ӳ��
// 2: ���+ƽ����ֵ
// 3: ���+���Բ�ֵ
#define SIGMOID_OPTIMIZE 2
#if SIGMOID_OPTIMIZE >= 1
#define SIGMOID_PRECISION 500  // ʹ�þ���500��sigmoid��
#endif

#define ERROR_ERR_CMD_TYPE 1
#define ERROR_ERR_PARAM 2
#define ERROR_ERR_LACK_OF_MEM 3
#define ERROR_ERR_NET_NOT_INIT 4

typedef unsigned char uchar;
typedef unsigned char u16;

// �ڴ����
// ά����ȫ�ֱ�����
#if WORKING_MODE == 0
uchar layer_count;  //���� һ��Ҫ���ڵ���2
uchar* neurons_count_list;  //ÿ�����Ԫ������ָ����ڴ�����heap_memory��
float* weight_matrix;  //Ȩֵ����ָ����ڴ�����heap_memory��
u16 weight_matrix_len;
float*
    evaluate_tmp_mem;  // �����������ʱ�ڴ棬�䳤��Ϊneurons_count_list���Ԫ�ص�ֵ
uchar evaluate_tmp_mem_len;  // ������ʱ�ڴ�ĳ���
#elif WORKING_MODE == 1
#include <static_mode.h>
#endif

#if USE_IDATA_IN_HEAP && !USE_LARGE
idata
#endif
    uchar user_space_mem[USER_HEAP_MEM_SIZE];

// HeapMemory
#if WORKING_MODE == 0
#if USE_IDATA_IN_HEAP && !USE_LARGE
idata
#endif
    uchar heap_memory[HEAP_MEMORY_SIZE];
u16 used_mem;  // heap_memoryʹ�õ��ڴ�
uchar NewMem(uchar* ptr, u16 count) {
  if (used_mem + count > HEAP_MEMORY_SIZE)
    return ERROR_ERR_LACK_OF_MEM;  //���ڴ治��
  ptr = &heap_memory[used_mem];
  used_mem += count;
  return 0;
}
#endif

uchar CopyMem(uchar* src_ptr, uchar* dest_ptr, u16 len) {
  idata u16 i;
  for (i = 0; i < len; i++) {
    dest_ptr[i] = src_ptr[i];
  }
  return 0;
}
// ===============

// IO��
void ReadNByte(uchar* dat, u16 n, uchar use_user_space) {
  uchar i;
  if (use_user_space) dat = user_space_mem;  // ��ָ�붨λ���û����ڴ���
  for (i = 0; i < n; i++) {
		while (!RI)
      ;
    dat[i] = SBUF;
    RI = 0;
  }
}

void ReadNFloat(float* dat, u16 n) {
  uchar* ptr = dat;
  ReadNByte(ptr, sizeof(float) * n, 1);  // ��float���ݾ����û����ڴ���
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

// ָ���

#define PING_ID 0
#if WORKING_MODE == 0
#define SET_STRUCT_ID 2
struct SET_STRUCT {
  uchar layer_count;  // ��ҪУ�飺���ڵ���2
  uchar* layers;
};

#define SET_WEIGHTS_ID 4
struct SET_WEIGHTS {
  uchar layer_id;  // ��ҪУ�飺����layer
  float* weights;
};
#endif

#define EVALUATE_ID 6
struct EVALUATE {
  float* input_data;  // ���ȹ̶�Ϊ�������Ԫ����
};

#define EVALUATE_ACK_ID 7
struct EVALUATE_ACK {  // �����EVALUATE����ͬ�ṹ�ģ������Ľ�������ת��
  float* output_data;  // ���ȹ̶�Ϊ�������Ԫ����
};

#define ERROR_ID 8
struct ERROR {
  uchar error_type;
};

union COMMAND {  // ���ù������Ż�RAM�ռ�ռ��
#if WORKING_MODE == 0
  struct SET_STRUCT set_struct;
  struct SET_WEIGHTS set_weights;
#endif
  struct EVALUATE evaluate;
  struct EVALUATE_ACK evaluate_ack;
  struct ERROR error;
};

#if WORKING_MODE == 0
void ComputeWeightMatrixLen() {
  uchar i;
  weight_matrix_len = 0;
  for (i = 1; i < layer_count; i++) {
    weight_matrix_len +=
        (neurons_count_list[i - 1] + 1) * neurons_count_list[i];
  }
}
#endif

u16 GetLayerWeightIndex(uchar layer) {
  uchar i;
  u16 result;
  for (i = layer; i >= 1; i--) {
    result += (neurons_count_list[i - 1] + 1) * neurons_count_list[i];
  }
  return result;
}

#if WORKING_MODE == 0
uchar set_struct(struct SET_STRUCT* param);
uchar set_weights(struct SET_WEIGHTS* param, u16 weights_count);
#endif
uchar evaluate(struct EVALUATE* param);

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
  idata union COMMAND cmd;
  uchar err;
#if WORKING_MODE == 0
  u16 tmp;
#endif
  while (1) {
    ReadNByte(&type_id, sizeof(type_id), 0);
    switch (type_id) {
      case PING_ID:
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        break;
#if WORKING_MODE == 0
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
#endif
      case EVALUATE_ID:
        ReadNFloat(cmd.evaluate.input_data, neurons_count_list[0]);
        err = evaluate(&cmd.evaluate);
        RETURN_ERROR
        type_id++;
        WriteNByte(&type_id, sizeof(type_id));
        WriteNFloat(cmd.evaluate_ack.output_data,
                    neurons_count_list[layer_count - 1]);
        break;
      default:
        err = ERROR_ERR_CMD_TYPE;
        RETURN_ERROR
    }
  }
}

// �����
#if WORKING_MODE == 0
uchar set_struct(struct SET_STRUCT* param) {
  uchar err;
  uchar i;
  evaluate_tmp_mem_len = 0;
  if (param->layer_count < 2) return ERROR_ERR_PARAM;
  layer_count = param->layer_count;
  err = NewMem(neurons_count_list, layer_count);
  if (err != 0) return err;  // ͸��������
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
    u16 weights_count) {  //ֱ�Ӵ������õ�Ȩ�ظ���������Ҫ�ڲ����¼���
  if (neurons_count_list == 0) return ERROR_ERR_NET_NOT_INIT;
  if (param->layer_id >= layer_count ||
      param->layer_id < 1)  //�������õ�һ��������Ȩֵ����
    return ERROR_ERR_PARAM;
  CopyMem((uchar*)(param->weights),
          (uchar*)(weight_matrix + GetLayerWeightIndex(param->layer_id)),
          weights_count);
  return 0;
}
#endif
#define START_POINT -100
#define SG_LEN 200
#if SIGMOID_OPTIMIZE >= 1
#include "sigmoid_table.h"
float GetSigmoid(int index) {  //�ɽ���sigmoid�߽���
  if (index < 0) return 0;
  if (index > SIGMOID_PRECISION) return 1;
  return sigmoid_table[index];
}
#endif
#if SIGMOID_OPTIMIZE == 0
#include <math.h>
float sigmoid(float n) { return 1 / (1 + exp(-n)); }
#elif SIGMOID_OPTIMIZE == 1
float sigmoid(float n) {
  return GetSigmoid((int)(SIGMOID_PRECISION * (n - START_POINT) / SG_LEN));
}
#elif SIGMOID_OPTIMIZE == 2
#include <math.h>
float sigmoid(float n) {
  return (GetSigmoid((u16)ceil(n)) + GetSigmoid((u16)floor(n))) / 2;
}
#elif SIGMOID_OPTIMIZE == 3
#include <math.h>
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
  idata uchar i;
  idata uchar j;
  idata uchar k;
  idata float* ptr = weight_matrix;
  idata uchar* layer_ptr = weight_matrix + GetLayerWeightIndex(1);
  idata float* input_data = param->input_data;
  for (i = 1; i < layer_count; i++) {
    for (j = 0; j < neurons_count_list[j]; j++) {
      evaluate_tmp_mem[j] = 0;
      for (k = 0; k < neurons_count_list[j - 1]; k++) {
        evaluate_tmp_mem[j] += input_data[j - 1] * *ptr;  // Ȩ��
        ptr++;
      }
      evaluate_tmp_mem[j] -= *ptr;  //��ֵ
      evaluate_tmp_mem[j] = sigmoid(evaluate_tmp_mem[j]);
      ptr++;
    }
    CopyMem((uchar*)evaluate_tmp_mem, (uchar*)input_data,
            neurons_count_list[j]);  // ����ǰ��������Ϊ��һ�������
  }
  // ѭ��������input_data�Ѿ�����������
  return 0;
}

int main() {
  SCON = 0X50;  //����Ϊ������ʽ1
  TMOD = 0X20;  //���ü�����������ʽ2
  PCON = 0X80;  //�����ʼӱ�
  TH1 = 0XF3;   //��������ʼֵ���ã�������4800
  TL1 = 0XF3;
  TR1 = 1;  //�򿪼�����
  ReadPacket();
  return 0;
}
