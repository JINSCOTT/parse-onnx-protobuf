# Very basics of parsing onnx weight file(".onnx") with c++ and protobuf.
* The code is written only show a glimpse of how parsing is done with protobuf
* Protobuf is installed with vcpgk
## Installing protobuf
* Got to the root directory of the project(where the .sln file is).
* Use Visual Studio command prompt to execute command
"vcpkg new --application"
* edit "vcpkg.json". Similar to the vcpkg.json in this project.
* Use Visual Studio command prompt to execute command
"vcpkg install"
* Include the headers"vcpkg_installed\x64-windows\include"
* Link the "libprotobuf.lib" in "vcpkg_installed\x64-windows\lib"
* Copy the "libprotobuf.dll" in "vcpkg_installed\x64-windows\tools\protobuf" into the project.

## Some experiences during parsing and trying to write infer
* Parse the inputs and outputs, ValueInfo, first. They contain the inputs and outputs of the model and some of the layers, especially the weights of nodes.
* Secondly, parse the initializers. They contain the actual data and dimensions of the weights.
* Finally parse the nodes. With some of the ValueInfo and their actual dimensions none, hypothesizing the dimensions of ValueInfo not in inputs and outputs is possible so that they can be created. They should be created so that every input and output of nodes can be linked.
* With inputs and outputs linked for the nodes, executing the model can be done by executing the nodes sequentially. Fetch the tensors in the input ValueInfo for execution, and store the results in the output ValueInfo. 

# reference 
1. https://stackoverflow.com/questions/67301475/parse-an-onnx-model-using-c-extract-layers-input-and-output-shape-from-an-on
2. https://onnx.ai/onnx/api/classes.html
