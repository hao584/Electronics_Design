#include "bsp_OLED.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "font.h"



#define SCL_0    OLED_SCL_GPIO_Port->BSRR = OLED_SCL_Pin << 16
#define SCL_1    OLED_SCL_GPIO_Port->BSRR = OLED_SCL_Pin
#define SDA_0    OLED_SDA_GPIO_Port->BSRR = OLED_SDA_Pin << 16
#define SDA_1    OLED_SDA_GPIO_Port->BSRR = OLED_SDA_Pin



/*****************************************************************************
 ** ȫ�ֱ���
****************************************************************************/
typedef struct                  // OLED ��Ҫ������
{
    uint16_t width;			    // OLED ���
    uint16_t height;		    // OLED �߶�
    uint8_t  FlagInit;          // ��ʼ����ɱ�־
} xOLED_TypeDef;
xOLED_TypeDef xLCD;	            // ����LCD��Ҫ����



uint8_t OLED_GRAM[128][8];



/******************************************************************************
 * ��  ���� delay_ms
 * ��  �ܣ� ms ��ʱ����
 * ��  ע�� 1��ϵͳʱ��168MHz
 *          2���򹴣�Options/ c++ / One ELF Section per Function
            3�������Ż�����Level 3(-O3)
 * ��  ���� uint32_t  ms  ����ֵ
 * ����ֵ�� ��
 ******************************************************************************/
static volatile uint32_t ulTimesMS;    // ʹ��volatile��������ֹ�������������Ż�
static void delay_ms(uint16_t ms)
{
    ulTimesMS = ms * 16500;
    while (ulTimesMS)
        ulTimesMS--;                   // �����ⲿ��������ֹ��ѭ�����������Ż���
}



//��ʱ
static volatile uint32_t ulTimesUS;    // ʹ��volatile��������ֹ�������������Ż�
static void delay(void)
{
    ulTimesUS = 15;
    while (ulTimesUS--);
}



//��ʼ�ź�
static void start(void)
{
    SDA_1;
    SCL_1;
    delay();
    SDA_0;
    delay();
    SCL_0;
    delay();
}

//�����ź�
static void stop(void)
{
    SDA_0;
    SCL_1;
    delay();
    SDA_1;
}

//�ȴ��ź���Ӧ
static void waitACK(void)
{
    SDA_1;
    delay();
    SCL_1;
    delay();
    SCL_0;
    delay();
}

//д��һ���ֽ�
static void sendByte(uint8_t dat)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (dat & 0x80)
        {
            SDA_1;
        }
        else
        {
            SDA_0;
        }
        delay();
        SCL_1;
        delay();
        SCL_0;
        dat <<= 1;
    }
}

// ��������
static void writeCMD(uint8_t cmd)
{
    start();
    sendByte(0x78);  // ��ַ
    waitACK();
    sendByte(0x00);  // ���0x0
    waitACK();
    sendByte(cmd);   // ����ֵ
    waitACK();
    stop();
}

// ��������
//static void writeData(uint8_t data)
//{
//    start();
//    sendByte(0x78);  // ��ַ
//    waitACK();
//    sendByte(0x40);  // ���0x1
//    waitACK();
//    sendByte(data);  // ����ֵ
//    waitACK();
//    stop();
//}



//���㣬x:0~127��y:0~63��t:1 ��� 0,���
static void drawPoint(uint8_t x, uint8_t y, uint8_t t)
{
    uint8_t i, m, n;
    i = y / 8;
    m = y % 8;
    n = 1 << m;
    if (t)
    {
        OLED_GRAM[x][i] |= n;
    }
    else
    {
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
        OLED_GRAM[x][i] |= n;
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
    }
}



/******************************************************************
 * �������� OLED_Init
 * ��  �ܣ� OLED�ĳ�ʼ��,
 * ��  ���� ��
 * ��  ��:  ��
 *****************************************************************/
void OLED_Init(void)
{
    delay_ms(100);

    writeCMD(0xAE); //--turn off oled panel
    writeCMD(0x00); //---set low column address
    writeCMD(0x10); //---set high column address
    writeCMD(0x40); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    writeCMD(0x81); //--set contrast control register
    writeCMD(0xCF); // Set SEG Output Current Brightness
    writeCMD(0xA1); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    writeCMD(0xC8); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    writeCMD(0xA6); //--set normal display
    writeCMD(0xA8); //--set multiplex ratio(1 to 64)
    writeCMD(0x3f); //--1/64 duty
    writeCMD(0xD3); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    writeCMD(0x00); //-not offset
    writeCMD(0xd5); //--set display clock divide ratio/oscillator frequency
    writeCMD(0x80); //--set divide ratio, Set Clock as 100 Frames/Sec
    writeCMD(0xD9); //--set pre-charge period
    writeCMD(0xF1); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    writeCMD(0xDA); //--set com pins hardware configuration
    writeCMD(0x12);
    writeCMD(0xDB); //--set vcomh
    writeCMD(0x40); //Set VCOM Deselect Level
    writeCMD(0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)
    writeCMD(0x02); //
    writeCMD(0x8D); //--set Charge Pump enable/disable
    writeCMD(0x14); //--set(0x10) disable
    writeCMD(0xA4); // Disable Entire Display On (0xa4/0xa5)
    writeCMD(0xA6); // Disable Inverse Display On (0xa6/a7)
    OLED_Clear();
    writeCMD(0xAF);

    xLCD.FlagInit = 1;
    xLCD.width = 128;
    xLCD.height = 64;
}



/******************************************************************
 * �������� OLED_ColorTurn
 * ��  �ܣ� ���Ժ���
 * ��  ���� uint8_t i   0_������ʾ��1_��ɫ��ʾ
 * ��  �أ� ��
 *****************************************************************/
void OLED_ColorTurn(uint8_t i)
{
    if (i == 0)
    {
        writeCMD(0xA6);   // ������ʾ
    }
    if (i == 1)
    {
        writeCMD(0xA7);   // ��ɫ��ʾ
    }
}



/******************************************************************
 * �������� OLED_DisplayTurn
 * ��  �ܣ� ��Ļ��ת180��
 * ��  ���� uint8_t i   0_������ʾ��1_ˮƽ��ת��ʾ
 * ��  �أ� ��
 *****************************************************************/
void OLED_DisplayTurn(uint8_t i)
{
    if (i == 0)
    {
        writeCMD(0xC8); //������ʾ
        writeCMD(0xA1);
    }
    if (i == 1)
    {
        writeCMD(0xC0); //��ת��ʾ
        writeCMD(0xA0);
    }
}


/******************************************************************
 * �������� OLED_Display
 * ��  �ܣ� ����OLED��ʾ
 * ��  ���� uint8_t   sw   0_�ر���ʾ��1_����ʾ
 * ��  �أ� ��
 *****************************************************************/
void OLED_Display(uint8_t sw)
{
    writeCMD(0x8D);       // ��ɱ�ʹ��
    if (sw)
    {
        writeCMD(0x14);   // ������ɱ�
        writeCMD(0xAF);   // ������Ļ
    }
    else
    {
        writeCMD(0x10);   // �رյ�ɱ�
        writeCMD(0xAE);   // �ر���Ļ
    }
}



/******************************************************************
 * �������� OLED_Refresh
 * ��  �ܣ� �����Դ浽OLED
 * ��  ���� ��
 * ��  �أ� ��
 *****************************************************************/
void OLED_Refresh(void)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        writeCMD(0xb0 + i); // ��������ʼ��ַ
        writeCMD(0x00);     // ���õ�����ʼ��ַ
        writeCMD(0x10);     // ���ø�����ʼ��ַ
        start();
        sendByte(0x78);
        waitACK();
        sendByte(0x40);
        waitACK();
        for (uint8_t n = 0; n < 128; n++)
        {
            sendByte(OLED_GRAM[n][i]);
            waitACK();
        }
        stop();
    }
}



/******************************************************************
 * �������� OLED_Clear
 * ��  �ܣ� ��������
 * ��  ���� ��
 * ��  �أ� ��
 *****************************************************************/
void OLED_Clear(void)
{
    memset(OLED_GRAM, 0, 8 * 128); // ���������������
    OLED_Refresh();                // ������ʾ
}



/******************************************************************
 * �������� OLED_Line
 * ��  �ܣ� ��ֱ��
 * ��  ���� uint16_t x1     ���X����
 *          uint16_t y1     ���Y����
 *          uint16_t x2     �յ�X����
 *          uint16_t y2     �յ�Y����
 *          uint16_t color  ��ɫֵ
 * ��  ע��
 *****************************************************************/
void OLED_Line(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2)
{
    uint16_t  t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;                        // ������������
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)incx = 1;                 // ���õ�������
    else if (delta_x == 0)incx = 0;           // ��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0;           // ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)distance = delta_x; // ѡȡ��������������
    else distance = delta_y;
    for (t = 0; t <= distance + 1; t++)       // �������
    {
        drawPoint(uRow, uCol, 1);             // ����
        xerr += delta_x ;
        yerr += delta_y ;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
    OLED_Refresh();  // �����Դ浽OLED
}



/******************************************************************
 * �������� OLED_Circle
 * ��  �ܣ� ��ָ��λ�û�Բ
 * ��  ���� uint16_t Xpos     X����
 *          uint16_t Ypos     ���Y����
 *          uint16_t Radius   �뾶
 * ��  ע��
 *****************************************************************/
void OLED_Circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
    int16_t mx = Xpos, my = Ypos, x = 0, y = Radius;
    int16_t d = 1 - Radius;
    while (y > x)
    {
        drawPoint(x + mx, y + my, 1);
        drawPoint(-x + mx, y + my, 1);
        drawPoint(-x + mx, -y + my, 1);
        drawPoint(x + mx, -y + my, 1);
        drawPoint(y + mx, x + my, 1);
        drawPoint(-y + mx, x + my, 1);
        drawPoint(y + mx, -x + my, 1);
        drawPoint(-y + mx, -x + my, 1);
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    OLED_Refresh();  // �����Դ浽OLED
}



/******************************************************************
 * �������� OLED_ShowChinese
 * ��  �ܣ� ��ʾ����ȡģ�ĺ���,
 *          �ֿ�������font�ļ��У�ֻ�ʺ��������̶ֹ����
 *          PCtoLCD2018ȡģ������+����ʽ+����+C51��ʽ
 * ��  ���� uint16_t  x         ����x
 *          uint16_t  y         ����y
 *          uint8_t   index     ��ģ�����������е����
 * ��  ��:  ��
 *****************************************************************/
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1)
{
    uint8_t m, temp;
    uint8_t x0 = x, y0 = y;
    uint16_t size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; // �õ�����һ���ַ���Ӧ������ռ���ֽ���

    for (uint16_t i = 0; i < size3; i++)
    {
        if (size1 == 12)
        {
            temp = aFontChinese12[num][i];   // ����12*12����
        }
        else if (size1 == 16)
        {
            temp = aFontChinese16[num][i];   // ����16*16����
        }
        else if (size1 == 24)
        {
            temp = aFontChinese24[num][i];   // ����24*24����
        }
        else if (size1 == 32)
        {
            temp = aFontChinese32[num][i];   // ����32*32����
        }
        else
        {
            temp = aFontChinese12[num][i];   // ����ǷǷ����Σ������12*12����
        }
        for (m = 0; m < 8; m++)
        {
            if (temp & 0x01)
                drawPoint(x, y, 1);
            else
                drawPoint(x, y, 0);
            temp >>= 1;
            y++;
        }
        x++;
        if ((x - x0) == size1)
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
    OLED_Refresh();                          // �����Դ浽OLED
}



/******************************************************************
 * �������� drawAscii
 * ��  �ܣ� ��ָ��λ����ʾһ���ַ�
 * ��  ���� uint16_t x,y     ��ʼ����
 *          uint8_t  num     Ҫ��ʾ���ַ�:" "--->"~"
 *          uint8_t  size    �����С 12/16/24/32
 *****************************************************************/
static void drawAscii(uint16_t x, uint16_t y, uint8_t num, uint8_t size)
{
    static uint8_t temp;
    static uint8_t csize;
    static uint16_t y0;

    y0 = y;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);   // �õ�����һ���ַ���Ӧ������ռ���ֽ���
    num = num - ' ';                                          // �õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
    for (uint8_t t = 0; t < csize; t++)
    {
        if (size == 12)         temp = aFontASCII12[num][t];  // ����1206����
        else if (size == 16)    temp = aFontASCII16[num][t];  // ����1608����
        else if (size == 24)    temp = aFontASCII24[num][t];  // ����2412����
        else if (size == 32)    temp = aFontASCII32[num][t];  // ����3216����
        else return;                                          // û�е��ֿ�

        for (uint8_t t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80) drawPoint(x, y,  1);             // ���� ����
            else             drawPoint(x, y,  0);             // ���� ����

            temp <<= 1;
            y++;
            if (y >= xLCD.height)    return;                  // ������Ļ�߶�(��)
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                if (x >= xLCD.width) return;                  // ������Ļ���(��)
                break;
            }
        }
    }
}







/******************************************************************************
 * ��  ���� OLED_String
 * ��  �ܣ� ��LCD����ʾ�ַ���(֧��Ӣ�ġ�����)
 * ��  ���� Ӣ�ģ���ģ���ݱ�����font.h�������ʹ���һ�𱣴���оƬ�ڲ�Flash
 *          ���֣���ģ�������ⲿFlash�У��������ֿ���W25Q128��
 *                ħŮ��������W25Q128����¼����4���ֺŴ�С��ģ����
 * ��  ���� uint16_t   x      �������Ͻ�X����
 *          uint16_t   y      �������Ͻ�y����
 *          char*      pFont  Ҫ��ʾ���ַ�������
 *          uint8_t    size   �ֺŴ�С��12 16 24 32
 * ����ֵ:  ��
 ******************************************************************************/
void OLED_String(uint16_t x, uint16_t y, char *pFont, uint8_t size)
{
    if (xLCD .FlagInit == 0) return;

    uint16_t xStart = x;

    if (size != 12 && size != 16 && size != 24 && size != 32) // �����С����
        size = 24;

    while (*pFont != 0)                            // ������ȡ�ַ������ݣ�ֱ��'\0'ʱֹͣ
    {
        if (x > (xLCD.width - size))               // ��λ���жϣ����������ĩ���Ͱѹ�껻��
        {
            x = xStart;
            y = y + size;
        }
        if (y > (xLCD.height - size))              // ��λ���жϣ����������ĩ���ͷ��أ��������
            return;

        if (*pFont < 127)                          // ASCII�ַ�
        {
            drawAscii(x, y, *pFont, size);
            pFont++;
            x += size / 2;
        }
        else                                       // ������ʾ
        {

            pFont = pFont + 2;                     // ��һ��Ҫ��ʾ���������ڴ��е�λ��
            x = x + size;                          // ��һ��Ҫ��ʾ����������Ļ�ϵ�Xλ��
        }
    }
    OLED_Refresh();                                // �����Դ浽OLED
}








