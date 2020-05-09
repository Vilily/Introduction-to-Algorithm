#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/wait.h>

void mem_addr(unsigned long vaddr, unsigned long* paddr)
{
    int pageSize = getpagesize(); //���ô˺�����ȡϵͳ�趨��ҳ���С
    printf("ҳ���СΪ%d\n", pageSize);

    unsigned long v_pageIndex = vaddr / pageSize; //����������ַ�����0x0�ľ�����ҳ����
    printf("ҳ����Ϊ��%u\n", v_pageIndex);
    unsigned long v_offset = v_pageIndex * sizeof(uint64_t); //������/proc/pid/page_map�ļ��е�ƫ����
    unsigned long page_offset = vaddr % pageSize;            //���������ַ��ҳ���е�ƫ����
    printf("ƫ����Ϊ��%x\n", page_offset);
    uint64_t item = 0;                             //�洢��Ӧ���ֵ
    int fd = open("/proc/self/pagemap", O_RDONLY); //��ֻ����ʽ��/proc/pid/page_map

    lseek(fd, v_offset, SEEK_SET);                         //���α��ƶ�����Ӧλ�ã�����Ӧ�����ʼ��ַ���ж��Ƿ��ƶ�ʧ��
    read(fd, &item, sizeof(uint64_t)) != sizeof(uint64_t); //��ȡ��Ӧ���ֵ��������item�У����ж϶�ȡ����λ���Ƿ���ȷ

    if ((((uint64_t)1 << 63) & item) == 0) //�ж�present�Ƿ�Ϊ0
    {
        printf("page present is 0\n");
        return;
    }
    printf("����ҳ��Ϊ%u\n", ((uint64_t)1 << 63) & item);
    uint64_t phy_pageIndex = (((uint64_t)1 << 55) - 1) & item; //��������ҳ�ţ���ȡitem��bit0-54
    printf("����ҳ��Ϊ%u\n", item);
    *paddr = (phy_pageIndex * pageSize) + page_offset; //�ټ���ҳ��ƫ�����͵õ��������ַ
}

const int a = 100; //ȫ�ֳ���
int main()
{
    unsigned long phy = 0; //�����ַ

    mem_addr((unsigned long)&a, &phy);
    printf("����idΪ = %d, �����ַΪ = %x , �����ַΪ = %x\n", getpid(), &a, phy);
    sleep(10);
    //waitpid();
    return 0;
}