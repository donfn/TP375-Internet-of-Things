#include <nvs_flash.h>

void setup() {
  nvs_flash_erase(); // Diagrafh NVS 
  nvs_flash_init(); // Arxikopoihsh NVS
  while(true);
}

void loop() {

}
