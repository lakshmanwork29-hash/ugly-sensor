#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#define REG_COUNT 4
#define SENSOR_REG_BASE		0x3000
#define SENSOR_OK_VALUE		0x6000
#define SENSOR_MODE_1_VALUE	0x6002
#define SENSOR_MODE_2_VALUE	0x6004
#define DEVICE_NAME_LENGTH 32
#define SQUARE(x) ((x)*(x))

typedef struct { 
  uint32_t addr; 
  uint32_t val;
 } Reg_t;
int g_mode_count=0;
Reg_t *g_regs= NULL;

//fake i2c read 
uint32_t ReadReg(uint32_t a)
{ 
  return a * 2;
 }   
 
//validate the sensor name and initialize registers
int InitSensor(char *name)
{
  char DevName[DEVICE_NAME_LENGTH];
  int i,ret;
  int len;

if (name == NULL) {
	return -EINVAL;
}

len = snprintf(DevName,sizeof(DevName),"%s",name);

if (len < 0 || (size_t)len >= sizeof(DevName)) {
	return -EINVAL;
} 
  g_regs = malloc(REG_COUNT * sizeof(Reg_t));

  if (g_regs == NULL) {
    
    return  -ENOMEM;
  }

  for (i=0;i<REG_COUNT;i++){
      g_regs[i].addr = SENSOR_REG_BASE + i;
      g_regs[i].val = ReadReg(g_regs[i].addr);
  }

  if(g_regs[0].val == SENSOR_OK_VALUE){
      printf("sensor ok\n");
      printf("init done\n"); 
  
  }
   

  switch(g_regs[1].val) {
  case SENSOR_MODE_1_VALUE : 
        g_mode_count = 1;
         break;

  case SENSOR_MODE_2_VALUE : 
         g_mode_count = 2; 
         break;
  default :
    g_mode_count=0;
		break;
  }
  if(g_mode_count > 1){
    ret = 0;
  }
  else{
    ret = -1;
  }
  unsigned int limit = 10; 
  int t = -1;
  if (t < (int)limit){
    printf("t is small\n");
    t++;
  }   
  ret=SQUARE(ret + 1);
  free(g_regs);
  g_regs=NULL;
  return ret;


}
// main function
int main() { 
  int ret;
  ret=InitSensor("CameraSensor0"); 
  if(ret == -EINVAL){
    printf("Invalid sensor name");
    return EXIT_FAILURE;
  }
  else if(ret == -ENOMEM){
    printf("Memory allocation failed");
    return EXIT_FAILURE;
  }
  
  else{
    printf("Successfully executed");
  }
  return EXIT_SUCCESS; 
}