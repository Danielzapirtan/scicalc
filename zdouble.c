typedef struct {
	int msign;
	int sign;
	int mantissa[14];
	int exp10[2];
} zdouble;

extern zdouble add(zdouble x, zdouble y);
extern zdouble mul(zdouble x, zdouble y);

