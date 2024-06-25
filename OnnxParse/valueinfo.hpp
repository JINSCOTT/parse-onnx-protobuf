#include <vector>
#include <string>

#include "onnx.proto3.pb.h"
#include "Tensor.hpp"


namespace onp {

	/// <summary>
	/// Value info holds data dimensions during parsing and act as tensor holders during inference 
	/// </summary>
	class ValueInfo {
	public:
		ValueInfo(std::string name);
		ValueInfo(::onnx::AttributeProto);
		bool Compatible(Tensor* const t);
		void SetParams(std::vector<std::string> param);
		void SetDims(std::vector<std::int64_t> dims);
		void SetTensor(Tensor* tensor);
		void SetType(const int type);
		int GetType() const { return Type; }
		const std::vector<std::string>& GetParams() { return Params; }
		const std::vector<std::int64_t>& GetDims() { return Dims; }
		Tensor* GetTensor() { return t; }
		std::string GetName() { return Name; };
		void Print();
	private:
		std::string Name;
		int Type = 0;
		std::vector<std::string> Params;	// e,g, batch number in front
		std::vector<int64_t> Dims;			// others
		Tensor* t = NULL;
	};



}