#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <c_json/c_json.h>

char *loadFile(const char *path)
{
	FILE *file = fopen(path, "r");

	if(file == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	uint64_t length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = malloc(length + 1);
	fread(buffer, 1, length, file);
	buffer[length] = '\0';

	fclose(file);

	return buffer;
}

int main(int argc, char **argv)
{
	char *data = loadFile("res/test.json");

	CJ_Variable *var = CJ_Parse(data);
	if(var->type == CJ_TYPE_OBJECT)
	{
		CJ_Object *root = (CJ_Object *)var;
		
		for(CJ_Object_Iterator *iter = CJ_Object_IteratorBegin(root); iter != CJ_Object_IteratorEnd(root); iter = CJ_Object_IteratorNext(root, iter))
		{
			printf("%s -> ", iter->name);
			CJ_fprintf(stdout, iter->var);
		}
	}
	CJ_fprintf(stdout, var);

	free(data);
}
