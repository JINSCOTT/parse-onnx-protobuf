
#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace onp {
	template <typename t>class Tensor {
	public:
		Tensor(t* dat, std::vector<int64_t> shape, int TensorProto_DataType);
		~Tensor();
		void SetData(void* dat, std::vector<int64_t> shape, int TensorProto_DataType);
		const int GetType();
		void SetType(int type);
		// ByteSize
		int64_t GetDataSize();
		// Dimension Size
		int64_t GetSize();

		const char* GetData() const;
		const int dummy() { //
		};
		const std::vector<int64_t>& GetDims() const;
		void print();
	private:
		int Type = 0;
		std::vector<int64_t>Dims;
		char* Data = NULL;

	};


}