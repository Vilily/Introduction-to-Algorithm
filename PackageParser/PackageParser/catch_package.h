/**
 * @author: Bao Wenjie
 * @date: 2021/5/28
 */

#pragma once
#include "pcap.h"


/* ץȡ���ݰ� */
int catch_package(pcap_if_t* dev);

/* ÿ�β������ݰ�ʱ��libpcap�����Զ���������ص����� */
void packet_callback(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);