#include <stdio.h> // printf()
#include <stdlib.h> // strtol() - converting string to int
#include <string.h> // strlen() - length string
#include <errno.h> // For errno - fast exit from function, if appearance error
#include <math.h> // for pow(), added for Win, not added for Linux
//#include <arpa/inet.h> // inet_pton(), fast check argv[1] on conformity syntax IPv4, outside file in Windows, for Linux

// define envs:
char mask; // argv[2]
int oct_1 = 256, oct_2 = 256, oct_3 = 256, oct_4 = 256; // env for octet in argv1 (just print argument), split IPv4 on 4 octets
int int_mask = 0, active_oct = 0; // int mask, select active octet by mask
int ip_gate = 0, ip_min = 0, ip_max = 0, l = 0, ip_broadcast = 0; // dynamic envs for print octet result
int count = 1; // calculate count potencial hosts in network by mask
const int zero = 0, const_gate = 1, const_broadcast = 255; // envs constant for print octet result

// calculate, which octet we will use. Select active octet by mask
int calc_min_max(int min_max_mask) {
    switch(min_max_mask) // use check for 'case' - simple and work condition '1 =< x >= 30'
    {
        case 1 ... 7: // exclude /0, because whole network
        active_oct = oct_1;
        return active_oct;
        case 8 ... 15:
        active_oct = oct_2;
        return active_oct;
        case 16 ... 23:
        active_oct = oct_3;
        return active_oct;
        case 24 ... 30: // exclude /31, /32, because network without free pool IP-address
        active_oct = oct_4;
        return active_oct;
    }   
}

// function for calculate and print min-max IP : /0, /1-7, /8-15, /16-23, /24-30, /31, /32
// IP-address 'default gateway' include in min-max pool, but may be reserved in some system
int calc_0(int int_mask)
{
    printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", zero, zero, zero, zero, int_mask);
    printf("Count IP-address (max in IPv4):\t\t[4294967294]\n"); // (2^32) - 2 = 4 294 967 294
    // default gateway
    printf("IP-address default gateway (unlikely):\t[%d.%d.%d.%d]\n", zero, zero, zero, const_gate);
    // min-max address
    printf("IP-address min:\t\t\t\t[%d.%d.%d.2]\n", zero, zero, zero);
    printf("IP-address max:\t\t\t\t[%d.%d.%d.254]\n", const_broadcast, const_broadcast, const_broadcast);
    printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", const_broadcast, const_broadcast, const_broadcast, const_broadcast);
    exit(1);
    return 0;
}

int calc_1_7(int int_mask)
{
        int degree_1_7 = 8-int_mask; // 2^degree_1_7 count degree is /8 network
        int b = 1;  // b = count is /8 network (calculate include 0), if mask 6, b = 4
            while (degree_1_7 > 0)
            {
            b = b * 2; // count classing networks /8
            degree_1_7--;
            }
    int count_mask_1_7 = b-1;  // if mask 6, b = 4, count_mask_1_7 = 3 (first eq 0-3)
    if (count_mask_1_7 >= active_oct) // if first eq
    {
    ip_gate = 0; // if first eq
    ip_min = 0; // if first eq
    ip_max = count_mask_1_7;
    ip_broadcast = ip_max;
    // network
    printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", ip_gate, zero, zero, zero, int_mask);
    printf("Count IP-address:\t\t\t[%d]\n", count-2);
    // default gateway
    printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", ip_gate, zero, zero, const_gate);
    // min-max address
    printf("IP-address min:\t\t\t\t[%d.%d.%d.2]\n", ip_min, zero, zero);
    printf("IP-address max:\t\t\t\t[%d.%d.%d.254]\n", ip_max, const_broadcast, const_broadcast);
    printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", ip_broadcast, const_broadcast, const_broadcast, const_broadcast);
    exit(1);
    return 0;
    }

    for (l = b; l <= active_oct+b; l++)
    {
    ip_gate = l - b;
    ip_min = ip_gate;
    ip_max = l-1;
    ip_broadcast = ip_max;
    l = l + (b - 1); // l++ delay
    }

    if (l >= active_oct)
    {
        // network
        printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", ip_gate, zero, zero, zero, int_mask);
        printf("Count IP-address:\t\t\t[%d]\n", count-2);
        // default gateway
        printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", ip_gate, zero, zero, const_gate);
        // min-max address
        printf("IP-address min:\t\t\t\t[%d.%d.%d.2]\n", ip_min, zero, zero);
        printf("IP-address max:\t\t\t\t[%d.%d.%d.254]\n", ip_max, const_broadcast, const_broadcast);
        printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", ip_broadcast, const_broadcast, const_broadcast, const_broadcast);
        exit(1);
        return 0;
    }
    return 0;
}

int calc_8_15(int int_mask)
{
        int degree_8_15 = 16-int_mask; // 2^degree_8_15 count degree is /16 network
        int b = 1;  // b = count is /16 network (calculate include 0), if mask 14, b = 4
            while (degree_8_15 > 0)
            {
            b = b * 2; // count classing networks /16
            degree_8_15--;
            }
    int count_mask_8_15 = b-1;  // if mask 14, b = 4, count_mask_8_15 = 3 (first eq 0-3)
    if (count_mask_8_15 >= active_oct) // if first eq
    {
    ip_gate = 0; // if first eq
    ip_min = 0; // if first eq
    ip_max = count_mask_8_15; // if first eq
    ip_broadcast = ip_max;
    // network
    printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", oct_1, ip_gate, zero, zero, int_mask);
    printf("Count IP-address:\t\t\t[%d]\n", count-2);
    // default gateway
    printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", oct_1, ip_gate, zero, const_gate);
    // min-max address
    printf("IP-address min:\t\t\t\t[%d.%d.%d.2]\n", oct_1, ip_min, zero);
    printf("IP-address max:\t\t\t\t[%d.%d.%d.254]\n", oct_1, ip_max, const_broadcast);
    printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", oct_1, ip_broadcast, const_broadcast, const_broadcast);
    exit(1);
    return 0;
    }

    for (l = b; l <= active_oct+b; l++)
    {
    ip_gate = l - b;
    ip_min = ip_gate;
    ip_max = l-1;
    ip_broadcast = ip_max;
    l = l + (b - 1); // l++ delay
    }

    if (l >= active_oct)
    {
        // network
        printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", oct_1, ip_gate, zero, zero, int_mask);
        printf("Count IP-address:\t\t\t[%d]\n", count-2);
        // default gateway
        printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", oct_1, ip_gate, zero, const_gate);
        // min-max address
        printf("IP-address min:\t\t\t\t[%d.%d.%d.2]\n", oct_1, ip_min, zero);
        printf("IP-address max:\t\t\t\t[%d.%d.%d.254]\n", oct_1, ip_max, const_broadcast);
        printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", oct_1, ip_broadcast, const_broadcast, const_broadcast);
        exit(1);
        return 0;
    }
    return 0;
}

int calc_16_23(int int_mask)
{
    int degree_16_23 = 24-int_mask; // 2^degree_16_23 count degree is /24 network
    int b = 1;  // b = count is /24 network (calculate include 0), if mask 22, b = 4
        while (degree_16_23 > 0)
        {
        b = b * 2; // count classing networks /24
        degree_16_23--;
        }
    int count_mask_16_23 = b-1;  // if mask 22, b = 4, count_mask_16_23 = 3 (first eq 0-3)
    if (count_mask_16_23 >= active_oct) // if first eq
    {
        ip_gate = 0; // if first eq
        ip_min = 0; // if first eq
        ip_max = count_mask_16_23;
        ip_broadcast = ip_max;
            // network
            printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", oct_1, oct_2, ip_gate, zero, int_mask);
            printf("Count IP-address:\t\t\t[%d]\n", count-2);
            // default gateway
            printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, ip_gate, const_gate);
            // min-max address
            printf("IP-address min:\t\t\t\t[%d.%d.%d.2]\n", oct_1, oct_2, ip_min);
            printf("IP-address max:\t\t\t\t[%d.%d.%d.254]\n", oct_1, oct_2, ip_max);
            printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, ip_broadcast, const_broadcast);
        exit(1);
        return 0;
    }

    for (l = b; l <= active_oct+b; l++)
    {
        ip_gate = l - b;
        ip_min = ip_gate;
        ip_max = l-1;
        ip_broadcast = ip_max;
        l = l + (b - 1); // l++ delay
    }

    if (l >= active_oct)
    {
            // network
            printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", oct_1, oct_2, ip_gate, zero, int_mask);
            printf("Count IP-address:\t\t\t[%d]\n", count-2);
            // default gateway
            printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, ip_gate, const_gate);
            // min-max address
            printf("IP-address min:\t\t\t\t[%d.%d.%d.2]\n", oct_1, oct_2, ip_min);
            printf("IP-address max:\t\t\t\t[%d.%d.%d.254]\n", oct_1, oct_2, ip_max);
            printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, ip_broadcast, const_broadcast);
        exit(1);
        return 0;
    }
    return 0;
}

int calc_24_30(int int_mask)
{
    if (0+count-1 >= active_oct) // if first eq
    {
        ip_gate = l + 1; // if first eq
        ip_min = l + 2; // if first eq
        ip_max = l + (count - 2); // if first eq
        ip_broadcast = l + (count - 1);
            // network
            printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", oct_1, oct_2, oct_3, ip_gate-1, int_mask);
            printf("Count IP-address:\t\t\t[%d]\n", count-2);
            // default gateway
            printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_gate);
            // min-max address
            printf("IP-address min:\t\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_min);
            printf("IP-address max:\t\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_max);
            printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_broadcast);
        exit(1);
        return 0;
    }

    for (l = count; l <= active_oct+count; l++)
    {
        ip_gate = l - (count - 1);
        ip_min = l - (count - 2);
        ip_max = l - 2;
        ip_broadcast = l - 1;
        l = l + (count - 1); // l++ delay
    }

    if (l >= active_oct) 
    {
            // network
            printf("Network:\t\t\t\t[%d.%d.%d.%d/%d]\n", oct_1, oct_2, oct_3, ip_gate-1, int_mask);
            printf("Count IP-address:\t\t\t[%d]\n", count-2);
            // default gateway
            printf("IP-address default gateway:\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_gate);
            // min-max address
            printf("IP-address min:\t\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_min);
            printf("IP-address max:\t\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_max);
            printf("IP-address broadcast:\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, ip_broadcast);
        exit(1);
        return 0;
    }
    return 0;
}

// input IP, mask | output gate, min, max, broadcast address
int call_switch(int active_oct, int int_mask)
{
    switch(int_mask) // execute function for calculate min-max IP-address
    {
            case 0:
            calc_0 (int_mask);
            case 1 ... 7:
            calc_1_7(int_mask);
            case 8 ... 15:
            calc_8_15(int_mask);
            case 16 ... 23:
            calc_16_23(int_mask);
            case 24 ... 30:
            calc_24_30(int_mask);
            return 0;
        case 31:
        printf("2 IP-address in network: gateway (even) and broadcast (not even).\n"); // hardcode
        exit(1);
        return 0;
        case 32:
        printf("1 IP-address is whole network.\n"); // hardcode
        exit(1);
        return 0;
//        default:
//        return 0;
    }
}

int main(int argc, char **argv) // input arguments: IPv4, mask
{
    // 0_check. If no arguments - fixes the error "segmentation fault". Print and exit
    if(argc < 2) {
	    printf("Error #0000. No arguments. Please enter IP-address and mask (example: %s 192.168.1.0 24).\n", argv[0]);
		exit(1);
    }

    char *str_ipv4 = argv[1];
    char *chk_arg_help = "--help";
    
    // 1_check. Check 1st argument "--help". Print and exit
    // !!! now code work before first symbol eq, need argument "-" for execute "--help"
    // running help "--help"
    if ( *str_ipv4 == *chk_arg_help )
    {   // hardcode
        printf("usage ip-range /?\n");
        printf("example: ip-range 2.193.104.207 16\n");
        printf("------------------------------------------------------\n");
        printf("IP-address:\t\t\t\t[2.193.104.207]\n");
        printf("IP-mask:\t\t\t\t[16]\n");
        printf("Network:\t\t\t\t[2.193.0.0/16]\n");
        printf("Count IP-address:\t\t\t[65534]\n");
        printf("IP-address default gateway:\t\t[2.193.0.1]\n");
        printf("IP-address min:\t\t\t\t[2.193.0.2]\n");
        printf("IP-address max:\t\t\t\t[2.193.255.254]\n");
        printf("IP-address broadcast:\t\t\t[2.193.255.255]\n");
        printf("------------------------------------------------------\n");
        exit(1);
    }

    // 2_check. Check argument: IP + mask = "argc <3". Print and exit
    if(argc < 3) {
	    printf("Error #0001. Please enter IP-address and mask (example: %s 192.168.1.0 24).\n", argv[0]);
		exit(1);
    }

    // 3_check. Check IP:
    
    // IP split on octet (numbers)
    char *ip_char_oct = argv[1];
    char *char_oct = strtok (ip_char_oct, ".");
    int check_oct_count = 0;
    for (int i = 1; i < 5; i++)
    {
        if (i == 1) oct_1 = atoi(char_oct); // int oct_1 value  
        if (i == 2) oct_2 = atoi(char_oct); // int oct_2 value  
        if (i == 3) oct_3 = atoi(char_oct); // int oct_3 value  
        if (i == 4) oct_4 = atoi(char_oct); // int oct_4 value  
        char_oct = strtok(NULL, ".");
    }
    
    // Check argv[1] is IPv4 address:
    if (0 <= oct_1 && oct_1 <= 255) check_oct_count = check_oct_count + 1;
    if (0 <= oct_2 && oct_2 <= 255) check_oct_count = check_oct_count + 1;
    if (0 <= oct_3 && oct_3 <= 255) check_oct_count = check_oct_count + 1;
    if (0 <= oct_4 && oct_4 <= 255) check_oct_count = check_oct_count + 1;

    if (check_oct_count == 4) goto gotoprogramm_1;
    else 
    {
        printf("Error #0002. 1st argument not a IPv4 address (example: %s 192.168.1.0 24).\n", argv[0]);
        exit(1);
    }
    gotoprogramm_1:

    /* for Linux
    int n_1 = strlen(str_ipv4);
    int ip_version(const char *src) {
    char buf[INET6_ADDRSTRLEN];
    if (inet_pton(AF_INET, src, buf)) {
        return 4;
    }
    return -1;
    }

    // Check argv[1] is IPv4 address:
    if ( ip_version(str_ipv4) != 4 ) {
    printf("Error #0002. 1st argument not a IPv4 address (example: %s 192.168.1.0 24).\n", argv[0]);
    exit(1);
    }
    */

    // 4_check. Check mask:
    char *p;
    mask = strtol(argv[2], &p, 10);
    int_mask = mask;
    switch(int_mask) // use check for 'case' - simple and work condition '0 =< x >= 32'
    {
            case 0 ... 32:
            goto gotoprogramm_2; //go run main programm, mask is correctly
            return 0;
        default: 
        printf("Error #0003. 2nd argument != 0-32.\n"); // mask is not correctly, show message and exit programm
        exit(1);
        return 0;
    }   
    gotoprogramm_2:

    // Result:
    printf("IP-address:\t\t\t\t[%d.%d.%d.%d]\n", oct_1, oct_2, oct_3, oct_4);
    printf("IP-mask:\t\t\t\t[%d]\n", int_mask); // show masks
    //formula for callc degree by masks
    int x = 32 - int_mask;
    count = pow(2, x);

    // calculate count hosts by mask, for Linux
    /*
    int i = x;
        while (i > 0)
        {
        count = count * 2; // calculate count potencial hosts in network by mask
        i--;
        }
    */
    
    // calculate min-max address:
    switch(int_mask)
    {
        // can calculate with usage degree
        case 1 ... 30:
        calc_min_max(int_mask);
        goto result;
        return 0;
    }   

result:
call_switch(active_oct, int_mask); // function place in outside file "ip-range-min-max"

// Work on Windows
//    printf("Count IP-address: 2 ^ %d =\t%.f\n", x, pow(2, x));
    return 0;
}