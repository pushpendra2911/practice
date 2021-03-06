#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* strToBinary(char *buff, unsigned int len)
{
  char *binaryStr;
  int i = 0, j = 0, stuffOneCount = 0, stuffZeroCount = 0;
	int value;

	binaryStr = (char *) malloc((sizeof(char) * 9 * len)+1);

	while(buff[i] != '\0')
	{
		value = (int)buff[i];

		for(int k = 0; k <= 7; k++)
		{
			if(value%2 == 0)
			{
				binaryStr[j++] = '0';
				stuffOneCount = 0;
				stuffZeroCount++;

			}
			else
			{
				binaryStr[j++] = '1';
				stuffOneCount++;
				stuffZeroCount = 0;
			}

			if(stuffOneCount == 5)
			{
				binaryStr[j++] = '0';
				stuffOneCount = 0;
				stuffZeroCount++;
			}
            if(stuffZeroCount == 5)
            {
				binaryStr[j++] = '1';
				stuffZeroCount = 0;
				stuffOneCount++;
            }
			value = value/2;
		}
		i++;
	}
	binaryStr[j] = '\0';

	return binaryStr;
}

void reverse(char *buff)
{
	int i = 0, len = strlen(buff);
	char c;

	for(i = 0; i < len/2; i++)
	{
		c = buff[i];
		buff[i] = buff[len - i - 1];
		buff[len - i - 1] = c;
	}
}

char *binaryToStr(char *buff, int len)
{
	char *charStr;
	char data[9] = {0};
	int i = 0, j = 0, k = 0, addCount = 0, stuffOneCount = 0, stuffZeroCount = 0;

	charStr = (char*) malloc(((sizeof(char)*len)/8)+1);

	while(buff[i] != '\0')
	{
		if(buff[i] == '1')
		{
            if(stuffZeroCount != 5)
            {
                data[addCount++] = '1';
            }
            stuffZeroCount = 0;
			stuffOneCount++;
		}
		else
		{
			if(stuffOneCount != 5)
			{
				data[addCount++] = '0';				
			}
			stuffOneCount = 0;
            stuffZeroCount++;
		}

		if(addCount == 8)
		{
			data[addCount] = '\0';
			reverse(data);
			charStr[j++] = strtol(data, 0, 2);
			addCount = 0;
			memset(data, 0, 8);
		}

		i++;
	}
	charStr[j] = '\0';
	
	return charStr;
}


char* nrzi_encode_str(char *buff, int len)
{
    char *encodedStr, c;
    int i = 1, j = 0;

    encodedStr = (char*) malloc((sizeof(char) * len)+1);

    c = '0';
    encodedStr[j++] = '0';

    while(buff[i] != '\0')
    {
        if(buff[i] == '1')
        {
            if(c == '0')
            {
                encodedStr[j] = '1';
            }
            else
            {
                encodedStr[j] = '0';
            }
        }
        else
        {
            encodedStr[j] = c;
        }
        c = encodedStr[j];
        i++;
        j++;
    }
    encodedStr[j] = '\0';

    return encodedStr;
}



char* nrzi_decode_str(char *buff, int len)
{
    char *decodedStr, c;
    int i = 0, j = 0;

    decodedStr = (char*) malloc((sizeof(char) * len)+1);

    c = buff[i++];
    decodedStr[j++] = '0';

    while(buff[i] != '\0')
    {
        if(buff[i] == c)
        {
            decodedStr[j] = '0';
        }
        else
        {
            decodedStr[j] = '1';
        }
        c = buff[i];
        i++;
        j++;
    }
    decodedStr[j] = '\0';

    return decodedStr;
}




int main(int argc, char *argv[])
{
	char *buff;
	char *binaryStr, *charStr, *encodedStr, *decodedStr;
    
    if( argc == 2)
    {
        buff = strdup(argv[1]);
    }
    else if (argc > 2)
    {
        printf("Multiple argument not allowed!!\n");
        return -1;
    }
    else
    {
        printf("No string passed to encode and decode\n");
        return -1;
    }

	printf("Char String: %s\n", buff);

	binaryStr = strToBinary(buff, strlen(buff));
	printf("Binary String: %s\n", binaryStr);

    encodedStr = nrzi_encode_str(binaryStr, strlen(binaryStr));
    printf("NRZI Encoded String: %s\n", encodedStr);

    decodedStr = nrzi_decode_str(encodedStr, strlen(encodedStr));
    printf("NRZI Decoded String: %s\n", decodedStr);

	charStr = binaryToStr(decodedStr, strlen(decodedStr));
	printf("Char String after Decoding: %s\n", charStr);


	free(buff);
	free(binaryStr);
	free(charStr);
	free(encodedStr);
	free(decodedStr);
	return 0;
}
