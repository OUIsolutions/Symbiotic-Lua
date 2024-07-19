typedef struct {
	const char *path;
	long size;
	bool is_binary;
	unsigned char *content;
}Bin;
Bin bins[] = {

	{
		.path="test_unique.txt",
		.size=20,
		.is_binary=false,
		.content="\xa\x63\x6f\x6e\x74\x65\x6e\x74\x20\x69\x6e\x20\x65\x76\x65\x72\x79\x20\x6f\x73"
	},

	{
		.path="foder/"
	},

	{
		.path="foder/second_test.txt",
		.size=3,
		.is_binary=false,
		.content="\x73\x73\x73"
	},
};
