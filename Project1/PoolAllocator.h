#pragma once
#define CREATE(varName, blockCount, blockSize) PoolAllocator<blockCount,blockSize> varName;

class IHeap
{
public:
	virtual void* Allocate(size_t sizeInBytes) = 0;
	virtual void Deallocate(void *) = 0;
	virtual size_t Available() const = 0;
};

template<size_t t_blockCount, size_t t_blockSize>
class PoolAllocator : IHeap
{
private:
	const size_t blockSize = t_blockSize;
	const size_t blockCount = t_blockCount;
	char pool[t_blockCount*t_blockSize];
	int blockState[t_blockCount]; //0 - free // 1 - start // 2 - allocated // 3 - end
public:
	PoolAllocator() {
		for (size_t i = 0; i < blockCount; i++) {
			blockState[i] = 0;
		}
	}

	void* Allocate(size_t sizeInBytes) {
		void* ptr = nullptr;
		size_t blocks = static_cast<size_t>(static_cast<double>(sizeInBytes) / blockSize);
		if (sizeInBytes % blockSize) blocks++;
		for (size_t i = 0; i < blockCount; i++) {
			bool isFree = true;
			for (size_t j = 0; j < blocks; j++) {
				if (i + j > blockCount) {
					isFree = false; break;
				}
				if (blockState[i + j] > 0) {
					isFree = false; break;
				}
			}
			if (isFree) {
				blockState[i] = 1;
				for (size_t j = 1; j < blocks-1; j++) blockState[i + j] = 2;
				if (blocks > 1) {
					blockState[i + blocks - 1] = 3;
				}
				else {
					blockState[i] = 3;
				}
				ptr = static_cast<void*>(&pool[i]);
				break;
			}
		}
		return ptr;
	}

	void Deallocate(void* ptr) {
		for (size_t i = 0; i < blockCount; i++) {
			if (ptr == &pool[i]) {
				if (blockState[i] == 1) {
					while (blockState[i] != 3) {
						blockState[i++] = 0;
					}
					blockState[i] = 0;
					break;
				}
				else if (blockState[i] == 3) {
					if(i > 0){
						if (blockState[i - 1] == 3 || blockState[i-1] == 0) {
							while (blockState[i] != 3) {
								blockState[i++] = 0;
							}
							blockState[i] = 0;
							break;
						}
					}
					else {
						while (blockState[i] != 3) {
							blockState[i++] = 0;
						}
						blockState[i] = 0;
						break;
					}
				}
			}
		}
		return;
	}

	size_t Available() const {
		size_t available = 0;
		for (size_t i = 0; i < blockCount; i++) {
			if (blockState[i] == 0) available++;
		}
		return available*blockSize;
	}

	void printPool() {
		for (int i = 0; i < blockCount; i++) {
			printf("%d ", blockState[i]);
		}
		printf("%d\n", static_cast<int>(Available()));
	}
};