#pragma once

//����һ��������Ϊ��������ִ�и÷�����ִ����Ϻ���ִ�� checkError���� 
//  ����C#��Э����yield return һ���������������еķ���ִ����Ϻ��ڽ�����������ִ��
//Ҳ����unity Dotween��Ķ�������

//#ifdef DEBUG//Ԥ�����
//#define GL_CALL(fun)  fun;checkError();
//#else
#define GL_CALL(fun)  fun;
//#endif
void checkError();