#ifndef _SERIALIZE_
#define _SERIALIZE_

void* unserializeBytes(void* sourceBuffer, const char* key, const void* destinationBuffer);
void* serializeBytes(void* destinationBuffer, const char* key, const void* sourceBuffer, unsigned int sourceSize);

#endif