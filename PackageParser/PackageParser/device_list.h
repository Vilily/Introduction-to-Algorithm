/**
 * @author: Bao Wenjie
 * @date: 2021/5/28
 */

#pragma once
#include "pcap.h"


 /* ��ȡ�������豸�б� */
int get_device_list(bool is_print, pcap_if_t*& alldevs);

/* ��ӡ�豸��Ϣ */
void print_device(pcap_if_t* device);

/* ����IP */
char* iptos(u_long ip);

