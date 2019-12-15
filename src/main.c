#include <reg52.h>

#define HEAP_MEMORY_SIZE 128
#define USE_LARGE false         // �Ƿ�ʹ��Large ģʽ����
#define USE_IDATA_IN_HEAP true  // ���ڴ��Ƿ����idata����

typedef unsigned char uchar;
typedef unsigned char u16;

// IO��
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

// ָ���

#define PING_ID 0

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

#define EVALUATE_ID 6
struct EVALUATE {
  float* input_data;  // ���ȹ̶�Ϊ�������Ԫ����
};

#define EVALUATE_ACK_ID 7
struct EVALUATE_ACK {
  float* output_data;  // ���ȹ̶�Ϊ�������Ԫ����
};

#define ERROR_ID 8
struct ERROR {
  uchar error_type;
};
#define ERROR_ERR_CMD_TYPE 1
#define ERROR_ERR_PARAM 2
#define ERROR_ERR_LACK_OF_MEM 3
#define ERROR_ERR_NET_NOT_INIT 4

union COMMAND {  // ���ù������Ż�RAM�ռ�ռ��
  struct SET_STRUCT set_struct;
  struct SET_WEIGHTS set_weights;
  struct EVALUATE evaluate;
  struct EVALUATE_ACK evaluate_ack;
  struct ERROR error;
};

// ά����ȫ�ֱ�����
uchar layer_count;  //���� һ��Ҫ���ڵ���2
uchar* neurons_count_list;  //ÿ�����Ԫ������ָ����ڴ�����heap_memory��
float* weight_matrix;  //Ȩֵ����ָ����ڴ�����heap_memory��
unsigned short weight_matrix_len;
unsigned short used_mem;  // heap_memoryʹ�õ��ڴ�
#if USE_IDATA_IN_HEAP
idata
#endif
    uchar heap_memory[HEAP_MEMORY_SIZE];

uchar NewMem(uchar* ptr, uchar count) {
  if (used_mem + count > HEAP_MEMORY_SIZE)
    return ERROR_ERR_LACK_OF_MEM;  //���ڴ治��
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

// �����

uchar set_struct(struct SET_STRUCT* param) {
  uchar err;
  if (param->layer_count < 2) return ERROR_ERR_PARAM;
  layer_count = param->layer_count;
  err = NewMem(neurons_count_list, layer_count);
  if (err != 0) return err;  // ͸��������
  CopyMem(neurons_count_list, param->layers, layer_count);
  ComputeWeightMatrixLen();
}

uchar set_weights(
    struct SET_WEIGHTS* param,
    u16 weights_count) {  //ֱ�Ӵ������õ�Ȩ�ظ���������Ҫ�ڲ����¼���
  if (neurons_count_list == 0) return ERROR_ERR_NET_NOT_INIT;
  if (param->layer_id >= layer_count) return ERROR_ERR_PARAM;
}

int main() {}
