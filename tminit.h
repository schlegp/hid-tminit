#ifndef TMINIT_H
#define TMINIT_H

#include <linux/usb.h>

/*
 * This structs contains (in little endian) the response data
 * of the wheel to the request 73
 *
 * A sufficient research to understand what each field does is not
 * beign conducted yet. The position and meaning of fields are a
 * just a very optimistic guess based on instinct....
 */
struct __packed tm_wheel_response
{
	/*
	 * Seems to be the type of packet
	 * - 0x0049 if is data.a (15 bytes)
	 * - 0x0047 if is data.b (7 bytes)
	 */
	uint16_t type;

	union {
		struct __packed {
			uint16_t field0;
			uint16_t field1;
			/*
			 * Seems to be the model code of the wheel
			 * Read table thrustmaster_wheels to values
			 */
			uint8_t attachment;
			uint8_t model;

			uint16_t field2;
			uint16_t field3;
			uint16_t field4;
			uint16_t field5;
		} a;
		struct __packed {
			uint16_t field0;
			uint16_t field1;
			uint8_t attachment;
			uint8_t model;
		} b;
	} data;
};

struct tm_wheel {
	struct usb_device *usb_dev;
	struct usb_interface *interface;
	struct urb *urb;

	struct usb_ctrlrequest *model_request;
	struct tm_wheel_response *response;

	struct usb_ctrlrequest *change_request;
};

int thrustmaster_probe(struct tm_wheel *wheel, struct usb_interface *interface);
void thrustmaster_disconnect(struct tm_wheel *wheel);

#endif /* TMINIT_H */
