//
// Created by lavigne on 10/5/17.
//

# include "Module.h"

Module::Module() {}

Module::~Module() {}

char    Module::getOpcode()
{
    return (0x02);
}

void    *Module::getData()
{
  t_kbData *data;
  data = new t_kbData;

  data->timestamp = 193;
  data->key_code = 'A';
  return (void *)data;
}