#include "KEY.h" // ����������ص�ͷ�ļ������ж������밴����صĺ�ͺ���ԭ��


 
// ����ȫ�ֱ��������ڼ�¼ÿ�����������µĴ���
int Key1_Num ; // ��¼����1�����µĴ���
int Key2_Num ; // ��¼����2�����µĴ���
int Key3_Num ; // ��¼����3�����µĴ���
int16_t wait_time[SIZE_OF_WAIT] = {0}; // ����������ʱ��

//������ʼ��
void Key_Init ()
{
	Key1_Num = 0;
	Key2_Num = 0;
	Key3_Num = 0;

}

//��������
uint8_t Wait(uint8_t key)
{
    if (wait_time[key] >= 2)
    {
        wait_time[key]--;
        return 0;
    }
    else if ((wait_time[key] == 0) || (wait_time[key] == 1))
    {
        wait_time[key]--;
        return 1;
    }
    else
    {
        return 0;
    }
}

void SetWait(uint8_t key)
{
    wait_time[key] = 200;
}


// ����һ�����������ڻ�ȡ�������
void Get_KeyNum(void) 
{
    // ��ⰴ��1�Ƿ񱻰���
    if (IF_KEY_PRESSED_1 || Wait(KEY_1)) // ��ȡ�밴��1�������GPIO����״̬
    {
        if (Wait(KEY_1)) // ������������
        {
					Key1_Num++; // ���������²��ͷź����Ӱ���1�ļ���
        }
        
        if (IF_KEY_PRESSED_1)
            SetWait(KEY_1);
    }

    // ��ⰴ��2�Ƿ񱻰���
     if (IF_KEY_PRESSED_2 || Wait(KEY_2)) // ��ȡ�밴��1�������GPIO����״̬
    {
        if (Wait(KEY_2)) // ������������
        {
					Key2_Num++; // ���������²��ͷź����Ӱ���1�ļ���
        }
        
        if (IF_KEY_PRESSED_2)
            SetWait(KEY_2);
    }

    // ��ⰴ��3�Ƿ񱻰���
     if (IF_KEY_PRESSED_3 || Wait(KEY_3)) // ��ȡ�밴��1�������GPIO����״̬
    {
        if (Wait(KEY_3)) // ������������
        {
					Key3_Num++; // ���������²��ͷź����Ӱ���1�ļ���
        }
        
        if (IF_KEY_PRESSED_3)
            SetWait(KEY_3);
    }
}
