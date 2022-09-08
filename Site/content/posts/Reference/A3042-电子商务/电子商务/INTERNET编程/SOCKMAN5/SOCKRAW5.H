//	SOCKRAW.h
//	IP and ICMP data structures for raw sockets.

#define ICMP_ECHO 8						// An ICMP echo message
#define ICMP_ECHOREPLY 0			// An ICMP echo reply message
#define	ICMP_HEADERSIZE 8			// ICMP header size ("echo messages" only)

struct icmp										// Structure for an ICMP header
	{
		BYTE icmp_type;						// Type of message
		BYTE icmp_code;						// Type "sub code" (zero for echos)
		WORD icmp_cksum;					// 1's complement checksum
		WORD icmp_id;							// Unique ID (our handle)
		WORD icmp_seq;						// Datagram sequence number
		BYTE icmp_data[1];				// Start of the optional data
	};

struct ip 										// Structure for IP datagram header
	{
		BYTE ip_verlen;						// Version and header length
		BYTE ip_tos;							// Type of service
		WORD ip_len;							// Total packet length 
		UINT ip_id;								// Datagram identification 
		WORD ip_fragoff;					// Fragment offset 
		BYTE ip_ttl;							// Time to live 
		BYTE ip_proto;						// Protocol
		UINT ip_chksum;						// Checksum 
		IN_ADDR ip_src_addr;			// Source address 
		IN_ADDR ip_dst_addr;			// Destination address 
		BYTE ip_data[1];					// Variable length data area
	};
			
