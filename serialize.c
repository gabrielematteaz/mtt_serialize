#include "serialize.h"

/* Deserializza un blob da un buffer */
void* unserializeBytes(const void* sourceBuffer, const char* key, void* destinationBuffer)
{
	const char* source = sourceBuffer;
	char* destination = destinationBuffer;

	while (1)
	{
		unsigned char keySize = *source++; /* Leggo la dimensione della chiave */
		unsigned int destinationSize;

		if (keySize == 0) break; /* Il buffer è terminato */

		while (keySize) if (*key++ == *source++) keySize--; else break; /* Leggo la chiave */
		source = source + keySize; /* Ignoro la sezione non letta della chiave */

		destinationSize = *((unsigned int*)source)++; /* Leggo la dimensione del blob */

		if (keySize > 0) source = source + destinationSize; /* Ignoro la sezione non letta del blob */
		else
		{
			while (destinationSize--) *destination++ = *source++; /* Leggo il blob */

			break; /* La chiave è stata trovata */
		}
	}

	return destination; /* Restituisco la fine del buffer */
}

/* Serializza un blob in un buffer */
void* serializeBytes(void* destinationBuffer, const char* key, const void* sourceBuffer, unsigned int sourceSize)
{
	const char* const keyStart = key;
	unsigned char keySize;
	char* destination = destinationBuffer;
	const char* source = sourceBuffer;

	while (*key++); /* Vado alla fine della chiave */
	keySize = (unsigned char)(key - keyStart); /* Calcolo la dimensione della chiave */
	key = keyStart; /* Ripristino il puntatore */

	*destination++ = keySize; /* Scrivo la dimensione della chiave */

	while (keySize--) *destination++ = *key++; /* Scrivo la chiave */

	*((unsigned int*)destination)++ = sourceSize; /* Scrivo la dimensione del blob */

	while (sourceSize--) *destination++ = *source++; /* Scrivo il blob */

	*destination = 0; /* Aggiungo il terminatore */

	return destination; /* Restituisco la fine del buffer */
}