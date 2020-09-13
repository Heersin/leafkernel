#include <system.h>
extern int csr_x;

void print_log(unsigned char *log)
{
	settextcolor(WHITE, MAGENTA);
	puts("[Dev Log]");
	puts(log);
	putch('\n');
	settextcolor(WHITE, BLACK);
}

void print_info(unsigned char *info)
{
	putch('[');
	settextcolor(LIGHT_BLUE, BLACK);
	putch('*');
	settextcolor(WHITE, BLACK);
	putch(']');
	puts(info);
	putch('\n');
}
void print_success(unsigned char *info)
{
	putch('[');
	settextcolor(GREEN, BLACK);
	putch('+');
	settextcolor(WHITE, BLACK);
	putch(']');
	puts(info);
	putch('\n');
}
void print_debug(unsigned char *info)
{
	settextcolor(WHITE, BROWN);
	puts("[DEBUG]");
	puts(info);
	putch('\n');
	settextcolor(WHITE, BLACK);
}
void print_error(unsigned char *error)
{
	putch('[');
	settextcolor(RED, BLACK);
	putch('-');
	settextcolor(WHITE, BLACK);
	putch(']');
	puts(error);
	putch('\n');
}

void refreshLine(unsigned char *info)
{
	int len;
	int i;
	int csr_x_bak;
	unsigned char ch;
	unsigned char pre_ch;
	unsigned char test_mask;
	unsigned char upper_mask;
	unsigned char down_mask;

	csr_x = 0;
	test_mask = 0x40;
	upper_mask = 0xDF;		// & 1101 1111
	down_mask = 0x20;		// | 0010 0000
	len = strlen(info);
	for(i = 0; i < len; ++i)
	{

		csr_x_bak = i;
		csr_x = (i + 1) % (len-1);

		pre_ch = info[csr_x_bak];
		ch = info[csr_x];
		// 0b 0100 0001 -- A
		// 0b 0110 0001 -- a
		// > a
		// don't need to worry too large for | 0010 0000
		if(ch & test_mask)
		{
			ch &= upper_mask;
			putch(ch);
			csr_x = csr_x_bak;
			pre_ch |= down_mask;
			putch(pre_ch);
		}
		putch(ch);
	}
}

