#include <stdio.h>
#include <stdlib.h>
#define BUFLEN 256
#define TOKLEN 32

struct charncnt {
	char charval;
	unsigned int cnt;
	struct charncnt *next;
};

unsigned int nodecount(struct charncnt *head)
{
	unsigned int cnt = 0;
	for (; head != NULL; head = head->next, ++cnt)
		;
	return cnt;
}

unsigned int find_max(struct charncnt **head)
{
	unsigned int max = 0;
	struct charncnt *temp = *head;

	for (; temp != NULL; temp = temp->next)
		if (max < temp->cnt)
			max = temp->cnt;
	return max;
}

int addnode(struct charncnt **head, const char c)
{
	static struct charncnt *last = NULL;
	struct charncnt *newnode = (struct charncnt *)malloc(sizeof(struct charncnt));
	struct charncnt *temp = NULL;

	if (!newnode)
		return -1;
	newnode->charval = c;
	newnode->cnt = 1;
	newnode->next = NULL;
	if (!*head)
		*head = newnode;
	else {
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;        
	}
	return 0;
}

int findincr(struct charncnt **list, const char c)
{
	static struct charcnt *last = NULL;
	struct charncnt *temp = *list;

	while (temp) {
		if (c == temp->charval) {
			++temp->cnt;
			break;
		}
		temp = temp->next;
	}     
	if (!temp)
		return -1;
	return 0;
}

void findincr_or_add(struct charncnt **list, const char c, unsigned int *bars)
{
	if (findincr(list, c) == -1) {
		addnode(list, c);
		++*bars;
	}
}

unsigned int fill_lookup_list(const char *buf, struct charncnt **head)
{
	char c;
	unsigned int bars = 0;

	while (c = *buf++) {
		if (c == ' ' || c == '\t' || c == '\n')
		{
		} else
			findincr_or_add(head, c, &bars);

	}
	return bars;
}

void print_lower_boundary(unsigned int bars)
{
	printf("***\t");
	while (bars--)
		printf("  =  ");
	printf("\n");
}

void dump_lookup(struct charncnt *head)
{
	unsigned int i = 0;

	for (; head != NULL; head = head->next, ++i)
		printf("list[%d]\t-%d-\n", i, head->cnt);
}

unsigned int print_labels(struct charncnt *head)
{
	printf("***\t");
	while (head) {
		printf(" [%c] ", head->charval);
		head = head->next;
	}
	printf("\n");
}

unsigned int getnthcnt(const struct charncnt *head, unsigned int i)
{
	unsigned int cnt = 0;

	for (; (cnt < i && head != NULL); head = head->next, ++cnt)
	;
	if (head)
		return head->cnt;
	return 0;
}

void display_vert_freq_histogram(struct charncnt **head, unsigned int bars)
{
	unsigned int i, j;
	unsigned int max = find_max(head);
	unsigned int height = max;

	printf("Max in lookup: %d\n", height);
	for (i = height; i > 0; --i) {
		printf("(%d)\t", i);
		for (j = 0; j < bars; ++j)
			if (i <= getnthcnt(*head, j))
				printf("  *  ");
			else
				printf("     ");
		printf("\n");
	}
	if (height) {
		print_lower_boundary(bars);
		print_labels(*head);
	}
}

void print_vert_freq_histogram(const char *buf, struct charncnt **head)
{
	unsigned int bars = fill_lookup_list(buf, head);
	printf("Nodes in lookup: %d\n", bars);
	display_vert_freq_histogram(head, bars);
}

int main(int argc, char **argv)
{
	char buf[BUFLEN] = {'\0'};
	struct charncnt *head = NULL;

	printf("Please enter some text: ");
	if (!fgets(buf, BUFLEN, stdin)) {
		printf("Unable to read from input stream.");
		return -1;
	}
	printf("You have entered: %s", buf);
	print_vert_freq_histogram(buf, &head);
	return 0;
}

