// source: kactl
struct Reader {
	char buf[1 << 20];
	int it = 0, n = 0;
	char operator()() {
		if (it >= n) {
			buf[0] = 0;
			it = 0;
			n = fread(buf, 1, sizeof(buf), stdin);
		}
		return buf[it++];
	}
} reader;
int next_int() {
	char c;
	while (!isdigit((c = reader())));
	int a = c - '0';
	while (isdigit(c = reader())) a = a * 10 + c -'0';
	return a;
}
