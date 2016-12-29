#define NTOPICS 256
#define NPID 8

typedef void (*handler)();

#define	isbadtopic(x)	( ((topic16)(x) < 0) || \
			  ((topic16)(x) >= NTOPICS) )

struct msgqueue {
	umsg32	prmsg;
	topic16 topic;
	struct msgqueue *next;
};

struct topics {
	pid32   pids[NPID];
	handler handler[NPID];	
	int16	index;
};

extern	struct	topics topicTable[NTOPICS];
extern	struct	msgqueue *head;
extern	struct	msgqueue *tail;
extern 	pid32 bID;

