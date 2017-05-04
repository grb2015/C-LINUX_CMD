/****************************************************************************
 * lclnt1.c
 * License server client version 1
 *  link with lclnt_funcs1.o dgram.o
 */

 
/*  brief : ���֤����������ͻ���
            licence ������: û��û�кܶ�����ʹ�øó��򣬷���������Ʊ�ݸ�
*           �ͻ��˽��̣�������ɣ�����ﵽ�����ĳ���ʵ�����������������޿���
*           Ʊ�ݵ���Ϣ���ͻ�������֪ͨ�ͻ��Ժ����Ի��߹���֧�ֹ��ܸ����û��汾��
*           ���
*   history : 2017-05-05 renbin.guo created
*
*/   
#include <stdio.h>

int main(int ac, char *av[])
{
    // ���г�ʼ�������紴������UDP�׽��֡�������������addr�ȡ�
	setup();

	// �����������Ʊ�ݣ��Է��ʳ���
	if (get_ticket() != 0 )
		exit(0);
		
    // ����Ʊ�ݳɹ������������Ĺ���
	do_regular_work();

    // ����֮���ͷŵ�Ʊ��
	release_ticket();

	// �ػ��˳�
	shut_down();

}
/****************************************************************************
 * do_regular_work  the main work of the application goes here
 */
do_regular_work()
{
	printf("SuperSleep version 1.0 Running - Licensed Software\n");
	sleep(10);	/* our patented sleep algorithm */
}

