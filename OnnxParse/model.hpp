#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "onnx.proto3.pb.h"
#include "valueinfo.hpp"

namespace onp {
	class Model {
	public:
		// Load Model With Fname
		Model(const char* Fname);

		//std::vector<valueinfo const*> Inputs;
		//std::vector<valueinfo const*> Outputs;
	private:
		
		// Parse input values info
		void ParseInput(const google::protobuf::RepeatedPtrField< ::onnx::ValueInfoProto> Inputs);
		// Parse outputs values info
		void ParseOutput(const google::protobuf::RepeatedPtrField< ::onnx::ValueInfoProto> Outputs);
		// Weights
		void ParseInitializer(const google::protobuf::RepeatedPtrField< ::onnx::TensorProto> Initializers);
		// parse nodes layers
		void ParseNode(const google::protobuf::RepeatedPtrField< ::onnx::NodeProto> Nodes);

		std::string FileName;



		onnx::ModelProto model;
		//// 
		//std::vector < std::unique_ptr<Layer::Layer>> Layers;


		//std::map < std::string, std::unique_ptr<valueinfo>> Values;
		////std::map<std::string, std::unique_ptr<Tensor>> Tensors;





	};
}
