/* 
 * Thu Jun 19 15:37:12 CEST 2014
 * Riccardo Cecolin
 */ 
#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/hid.h>
#include <linux/input.h>

struct naga_translation {
  u16 from;
  u16 to;
};

static const struct naga_translation naga_sidepad_translation[] = {
  { KEY_1, KEY_F1 },
  { KEY_2, KEY_F2 },
  { KEY_3, KEY_F3 },
  { KEY_4, KEY_F4 },
  { KEY_5, KEY_F5 },
  { KEY_6, KEY_F6 },
  { KEY_7, KEY_F7 },
  { KEY_8, KEY_F8 },
  { }
};

static const struct naga_translation * naga_find_translation(u16 from)
{
  const struct naga_translation * t;

  for(t = naga_sidepad_translation; t->from; t++)
    if(t->from == from)
      return t;

  return NULL;
}

static int naga_event(struct hid_device *hdev, struct hid_field *field,
		      struct hid_usage *usage, __s32 value)
{
  const struct naga_translation * t;
  
  if((usage->hid & HID_USAGE_PAGE) == HID_UP_KEYBOARD)
    if((t = naga_find_translation(usage->code))) {
      input_event(field->hidinput->input, usage->type, t->to, value);
      return 1;
    }
  return 0;
}


static const struct hid_device_id naga_devices [] = {
  { HID_USB_DEVICE(0x1532, 0x0040) },
  { }
};

MODULE_DEVICE_TABLE(hid, naga_devices);

static struct hid_driver naga_driver = {
  .name = "hid-naga",
  .id_table = naga_devices,
  .event = naga_event,
};
  
module_hid_driver(naga_driver);

MODULE_LICENSE("GPL");
