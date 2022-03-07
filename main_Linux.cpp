#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    clock_t start, end;
    start = clock();
    FILE *rule = fopen(argv[1], "r");
    FILE *packet = fopen(argv[2], "r");
    FILE *res = fopen("res.txt", "w");
    if (rule == NULL || packet == NULL)
    {
        fprintf(res, "Error");
        exit(1);
    }
    int line, i;
    unsigned int ip[2][4], cidr[2], rule_port[2][2], rule_protocol[2], rule_ip[2], range[2];
    unsigned int packet_ip[2], packet_port[2], packet_protocol;
    while (!feof(packet))
    {
        fscanf(packet, "%d %d %d %d %d\n", &packet_ip[0], &packet_ip[1], &packet_port[0], &packet_port[1], &packet_protocol);
        for (line = 0; !feof(rule); line++)
        {
            fscanf(rule, "@%d.%d.%d.%d/%d %d.%d.%d.%d/%d %d : %d %d : %d %x/%x",
                   &ip[0][0], &ip[0][1], &ip[0][2], &ip[0][3], &cidr[0],
                   &ip[1][0], &ip[1][1], &ip[1][2], &ip[1][3], &cidr[1],
                   &rule_port[0][0], &rule_port[0][1], &rule_port[1][0], &rule_port[1][1],
                   &rule_protocol[0], &rule_protocol[1]);
            rule_ip[0] = ip[0][0] * 0x1000000 + ip[0][1] * 0x10000 + ip[0][2] * 0x100 + ip[0][3];
            rule_ip[1] = ip[1][0] * 0x1000000 + ip[1][1] * 0x10000 + ip[1][2] * 0x100 + ip[1][3];
            for (i = 0, range[0] = 1; i < 32 - cidr[0]; i++, range[0] *= 2)
                ;
            for (i = 0, range[1] = 1; i < 32 - cidr[1]; i++, range[1] *= 2)
                ;
            if (packet_ip[0] >= rule_ip[0] && packet_ip[0] <= rule_ip[0] + range[0] - 1 &&
                packet_ip[1] >= rule_ip[1] && packet_ip[1] <= rule_ip[1] + range[1] - 1 &&
                packet_port[0] >= rule_port[0][0] && packet_port[0] <= rule_port[0][1] &&
                packet_port[1] >= rule_port[1][0] && packet_port[1] <= rule_port[1][1])
            {
                if (packet_protocol == rule_protocol[0] && rule_protocol[1] == 0xFF ||
                    packet_protocol >= rule_protocol[0] && packet_protocol <= rule_protocol[1] && rule_protocol[1] != 0xFF ||
                    rule_protocol[1] == 0x00)
                {
                    break;
                }
            }
            fgetc(rule);
            fgetc(rule);
        }
        if (feof(rule))
        {
            fprintf(res, "-1\n");
        }
        else
        {
            fprintf(res, "%d\n", line);
        }
        rewind(rule);
    }
    fclose(rule);
    rule = NULL;
    fclose(packet);
    packet = NULL;
    fclose(res);
    res = NULL;
    end = clock();
    printf("%.2fs", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
