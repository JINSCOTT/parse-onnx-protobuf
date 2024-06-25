#include "model.hpp"


namespace onp {
	Model::Model(const char* Fname) {
		std::ifstream ModelFile(Fname, std::ios::in | std::ios::binary);     // Open file
		if (!ModelFile.is_open()) throw std::exception("Can't open file");
		onnx::ModelProto model;
		// Parse file from stream
		model.ParseFromIstream(&ModelFile);
	
		


	}
	void Model::ParseInput(const google::protobuf::RepeatedPtrField< ::onnx::ValueInfoProto> Inputs) {
		// Parse the input part to create valueinfo;
		int i = 0;
		std::vector<int64_t> dims;
		std::vector<std::string> params;
		ValueInfo* Info = NULL;

		for (auto ValInfo : Inputs)
		{

			dims.clear(); params.clear();
			Info = new ValueInfo(ValInfo.name());
			Info->SetType(ValInfo.type().tensor_type().elem_type());

			auto shape = ValInfo.type().tensor_type().shape();
			for (int i = 0; i < shape.dim_size(); i++) {
				switch (shape.dim()[i].value_case())
				{
				case onnx::TensorShapeProto_Dimension::ValueCase::kDimParam:
					params.push_back(shape.dim()[i].dim_param());
					break;
				case onnx::TensorShapeProto_Dimension::ValueCase::kDimValue:
					dims.push_back(shape.dim()[i].dim_value());
					break;
				default:
					assert(false && "should never happen");
				}
			}
			Info->SetParams(params);
			Info->SetDims(dims);
			this->Values.insert({ ValInfo.name(), std::unique_ptr<valueinfo>(Info) });
			this->Inputs.push_back(Info);
		}
	}
	




}