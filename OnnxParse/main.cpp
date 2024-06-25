// Expanded from the answer in https://stackoverflow.com/questions/67301475/parse-an-onnx-model-using-c-extract-layers-input-and-output-shape-from-an-on

#include <fstream>
#include <cassert>

#include "onnx.proto3.pb.h"

void print_dim(const ::onnx::TensorShapeProto_Dimension& dim)
{
    switch (dim.value_case())
    {
    case onnx::TensorShapeProto_Dimension::ValueCase::kDimParam:
        std::cout << dim.dim_param();
        break;
    case onnx::TensorShapeProto_Dimension::ValueCase::kDimValue:
        std::cout << dim.dim_value();
        break;
    default:
        assert(false && "should never happen");
    }
}

void print_io_info(const ::google::protobuf::RepeatedPtrField< ::onnx::ValueInfoProto >& info)
{
    for (auto input_data : info)
    {
        auto shape = input_data.type().tensor_type().shape();

        std::cout << "  " << input_data.name() << ":";
        std::cout << "[";
        if (shape.dim_size() != 0)
        {
            int size = shape.dim_size();
            for (int i = 0; i < size - 1; ++i)
            {
                print_dim(shape.dim(i));
                std::cout << ", ";
            }
            print_dim(shape.dim(size - 1));
        }
        std::cout << "]\n";
    }
}

void print_repeat_string(const ::google::protobuf::RepeatedPtrField< std::string >& strings)
{
    for (auto input_data : strings)
    {
        std::cout << input_data << " ";
    }
    std::cout << "\n";
}

void print_tensor_info(const ::google::protobuf::RepeatedPtrField< ::onnx::TensorProto >& tensors)
{
    for (auto t : tensors)
    {
        std::cout << t.raw_data();
        std::cout << "Data type: " << t.data_type() << " ,name: " << t.name() << " ,dim size: " << t.dims_size() << " ,dims: ";

        for (int i = 0; i < t.dims_size(); i++) {
            std::cout << t.dims()[i] << " ";
        }
        std::cout << "\n";
    }
}

void print_attributes(const ::google::protobuf::RepeatedPtrField< ::onnx::AttributeProto >& attrs)
{
    for (auto a : attrs)
    {
        std::cout << "Name: " << a.name() << ",  Type: " << a.type() << "\n";
    }
    std::cout << "\n";
}

void print_node_info(const ::google::protobuf::RepeatedPtrField< ::onnx::NodeProto >& nodes)
{
    for (auto input_data : nodes)
    {
        std::cout << "Node name: " << input_data.name() << " Type: " << input_data.op_type() << "\n";
        std::cout << "Node input: \n";
        print_repeat_string(input_data.input());
        std::cout << "Node output: \n";
        print_repeat_string(input_data.output());
        std::cout << "Attributes: \n";
        print_attributes(input_data.attribute());
    }
}

int main(int argc, char** argv)
{
    // Get some simpler pretrained model to begin with https://github.com/onnx/models
    std::ifstream input("resnet18-v1-7.onnx", std::ios::in | std::ios::binary);     // Open file
    onnx::ModelProto model;
    model.ParseFromIstream(&input);
    ::onnx::GraphProto graph = model.graph();

    std::cout << "graph inputs:\n";
    print_io_info(graph.input());

    std::cout << "graph outputs:\n";
    print_io_info(graph.output());

    std::cout << "Initializer: \n";
    print_tensor_info(graph.initializer());

    std::cout << "node info:\n";
    print_node_info(graph.node());

 
    return 0;
}