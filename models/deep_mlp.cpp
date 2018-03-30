// Auto generated by utensor-cli

#include "uTensor/core/context.hpp"
#include "uTensor/loaders/tensorIdxImporter.hpp"
#include "uTensor/ops/ArrayOps.hpp"
#include "deep_mlp.hpp"
#include "uTensor/ops/NnOps.hpp"
#include "uTensor/ops/MathOps.hpp"
#include "uTensor/core/tensor.hpp"
#include "uTensor/ops/MatrixOps.hpp"


void get_quant_model_ctx(Context& ctx, Tensor* input_0) {

{ // add tensor for placeholders
    ctx.add(input_0, "IteratorGetNext:0", 2);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/quant_model/Layer1_MatMul_eightbit_reshape_dims_0.idx"),
            "Layer1/MatMul_eightbit_reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "Layer1/MatMul_eightbit_reshape_IteratorGetNext:0", 2);
    ctx.push(new ReshapeOp(), 
             { "IteratorGetNext:0", "Layer1/MatMul_eightbit_reshape_dims:0" },
             { "Layer1/MatMul_eightbit_reshape_IteratorGetNext:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/quant_model/Layer1_MatMul_eightbit_reduction_dims_0.idx"),
            "Layer1/MatMul_eightbit_reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "Layer1/MatMul_eightbit_min_IteratorGetNext:0", 1);
    ctx.push(new MinOp(), 
             { "Layer1/MatMul_eightbit_reshape_IteratorGetNext:0", "Layer1/MatMul_eightbit_reduction_dims:0" },
             { "Layer1/MatMul_eightbit_min_IteratorGetNext:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "Layer1/MatMul_eightbit_max_IteratorGetNext:0", 1);
    ctx.push(new MaxOp(), 
             { "Layer1/MatMul_eightbit_reshape_IteratorGetNext:0", "Layer1/MatMul_eightbit_reduction_dims:0" },
             { "Layer1/MatMul_eightbit_max_IteratorGetNext:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Layer1/MatMul_eightbit_quantize_IteratorGetNext:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_quantize_IteratorGetNext:1", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_quantize_IteratorGetNext:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "IteratorGetNext:0",  "Layer1/MatMul_eightbit_min_IteratorGetNext:0", "Layer1/MatMul_eightbit_max_IteratorGetNext:0" },
             {  "Layer1/MatMul_eightbit_quantize_IteratorGetNext:0",  "Layer1/MatMul_eightbit_quantize_IteratorGetNext:1", "Layer1/MatMul_eightbit_quantize_IteratorGetNext:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.ubyte_import("/fs/constants/quant_model/Layer1_Variable_quint8_const_0.idx"),
            "Layer1/Variable_quint8_const:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/Layer1_Variable_min_0.idx"),
            "Layer1/Variable_min:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/Layer1_Variable_max_0.idx"),
            "Layer1/Variable_max:0",
            1);
}
{
    ctx.add(new RamTensor<int>(), "Layer1/MatMul_eightbit_quantized_mat_mul:0", 2);
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_quantized_mat_mul:1", 2);
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_quantized_mat_mul:2", 2);
    ctx.push(new QntMatMulOp<uint8_t, uint8_t, int>(), 
             { "Layer1/MatMul_eightbit_quantize_IteratorGetNext:0", "Layer1/MatMul_eightbit_quantize_IteratorGetNext:1", "Layer1/MatMul_eightbit_quantize_IteratorGetNext:2", "Layer1/Variable_quint8_const:0", "Layer1/Variable_min:0",  "Layer1/Variable_max:0" },
             { "Layer1/MatMul_eightbit_quantized_mat_mul:0", "Layer1/MatMul_eightbit_quantized_mat_mul:1",  "Layer1/MatMul_eightbit_quantized_mat_mul:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "Layer1/MatMul_eightbit_quantized_mat_mul:0", "Layer1/MatMul_eightbit_quantized_mat_mul:1", "Layer1/MatMul_eightbit_quantized_mat_mul:2" },
             { "Layer1/MatMul_eightbit_requant_range:0", "Layer1/MatMul_eightbit_requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Layer1/MatMul_eightbit_requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/MatMul_eightbit_requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "Layer1/MatMul_eightbit_quantized_mat_mul:0", "Layer1/MatMul_eightbit_quantized_mat_mul:1", "Layer1/MatMul_eightbit_quantized_mat_mul:2", "Layer1/MatMul_eightbit_requant_range:0", "Layer1/MatMul_eightbit_requant_range:1" },
             { "Layer1/MatMul_eightbit_requantize:0", "Layer1/MatMul_eightbit_requantize:1", "Layer1/MatMul_eightbit_requantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>(), "Layer1/MatMul:0", 1);
    ctx.push(new DequantizeOp(), 
             { "Layer1/MatMul_eightbit_requantize:0", "Layer1/MatMul_eightbit_requantize:1", "Layer1/MatMul_eightbit_requantize:2" },
             { "Layer1/MatMul:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/Layer1_Variable_1_0.idx"),
            "Layer1/Variable_1:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "Layer1/zscore:0", 2);
    ctx.push(new AddOp<float, float>(),
             { "Layer1/MatMul:0", "Layer1/Variable_1:0" }, 
             { "Layer1/zscore:0" });

    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/quant_model/Layer1_Relu_eightbit_reshape_dims_0.idx"),
            "Layer1/Relu_eightbit_reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "Layer1/Relu_eightbit_reshape_Layer1/zscore:0", 2);
    ctx.push(new ReshapeOp(), 
             { "Layer1/zscore:0", "Layer1/Relu_eightbit_reshape_dims:0" },
             { "Layer1/Relu_eightbit_reshape_Layer1/zscore:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/quant_model/Layer1_Relu_eightbit_reduction_dims_0.idx"),
            "Layer1/Relu_eightbit_reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "Layer1/Relu_eightbit_min_Layer1/zscore:0", 1);
    ctx.push(new MinOp(), 
             { "Layer1/Relu_eightbit_reshape_Layer1/zscore:0", "Layer1/Relu_eightbit_reduction_dims:0" },
             { "Layer1/Relu_eightbit_min_Layer1/zscore:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "Layer1/Relu_eightbit_max_Layer1/zscore:0", 1);
    ctx.push(new MaxOp(), 
             { "Layer1/Relu_eightbit_reshape_Layer1/zscore:0", "Layer1/Relu_eightbit_reduction_dims:0" },
             { "Layer1/Relu_eightbit_max_Layer1/zscore:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Layer1/Relu_eightbit_quantize_Layer1/zscore:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/Relu_eightbit_quantize_Layer1/zscore:1", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/Relu_eightbit_quantize_Layer1/zscore:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "Layer1/zscore:0",  "Layer1/Relu_eightbit_min_Layer1/zscore:0", "Layer1/Relu_eightbit_max_Layer1/zscore:0" },
             {  "Layer1/Relu_eightbit_quantize_Layer1/zscore:0",  "Layer1/Relu_eightbit_quantize_Layer1/zscore:1", "Layer1/Relu_eightbit_quantize_Layer1/zscore:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Layer1/Relu_eightbit_quantized:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/Relu_eightbit_quantized:1", 1);
    ctx.add(new RamTensor<float>({1}), "Layer1/Relu_eightbit_quantized:2", 1);
    ctx.push(new ReluOp<uint8_t, float, uint8_t>(), 
             { "Layer1/Relu_eightbit_quantize_Layer1/zscore:0", "Layer1/Relu_eightbit_quantize_Layer1/zscore:1", "Layer1/Relu_eightbit_quantize_Layer1/zscore:2" },
             { "Layer1/Relu_eightbit_quantized:0", "Layer1/Relu_eightbit_quantized:1", "Layer1/Relu_eightbit_quantized:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.ubyte_import("/fs/constants/quant_model/Layer2_Variable_quint8_const_0.idx"),
            "Layer2/Variable_quint8_const:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/Layer2_Variable_min_0.idx"),
            "Layer2/Variable_min:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/Layer2_Variable_max_0.idx"),
            "Layer2/Variable_max:0",
            1);
}
{
    ctx.add(new RamTensor<int>(), "Layer2/MatMul_eightbit_quantized_mat_mul:0", 2);
    ctx.add(new RamTensor<float>({1}), "Layer2/MatMul_eightbit_quantized_mat_mul:1", 2);
    ctx.add(new RamTensor<float>({1}), "Layer2/MatMul_eightbit_quantized_mat_mul:2", 2);
    ctx.push(new QntMatMulOp<uint8_t, uint8_t, int>(), 
             { "Layer1/Relu_eightbit_quantized:0", "Layer1/Relu_eightbit_quantized:1", "Layer1/Relu_eightbit_quantized:2", "Layer2/Variable_quint8_const:0", "Layer2/Variable_min:0",  "Layer2/Variable_max:0" },
             { "Layer2/MatMul_eightbit_quantized_mat_mul:0", "Layer2/MatMul_eightbit_quantized_mat_mul:1",  "Layer2/MatMul_eightbit_quantized_mat_mul:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "Layer2/MatMul_eightbit_requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer2/MatMul_eightbit_requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "Layer2/MatMul_eightbit_quantized_mat_mul:0", "Layer2/MatMul_eightbit_quantized_mat_mul:1", "Layer2/MatMul_eightbit_quantized_mat_mul:2" },
             { "Layer2/MatMul_eightbit_requant_range:0", "Layer2/MatMul_eightbit_requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Layer2/MatMul_eightbit_requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer2/MatMul_eightbit_requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "Layer2/MatMul_eightbit_requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "Layer2/MatMul_eightbit_quantized_mat_mul:0", "Layer2/MatMul_eightbit_quantized_mat_mul:1", "Layer2/MatMul_eightbit_quantized_mat_mul:2", "Layer2/MatMul_eightbit_requant_range:0", "Layer2/MatMul_eightbit_requant_range:1" },
             { "Layer2/MatMul_eightbit_requantize:0", "Layer2/MatMul_eightbit_requantize:1", "Layer2/MatMul_eightbit_requantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>(), "Layer2/MatMul:0", 1);
    ctx.push(new DequantizeOp(), 
             { "Layer2/MatMul_eightbit_requantize:0", "Layer2/MatMul_eightbit_requantize:1", "Layer2/MatMul_eightbit_requantize:2" },
             { "Layer2/MatMul:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/Layer2_Variable_1_0.idx"),
            "Layer2/Variable_1:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "Layer2/zscore:0", 2);
    ctx.push(new AddOp<float, float>(),
             { "Layer2/MatMul:0", "Layer2/Variable_1:0" }, 
             { "Layer2/zscore:0" });

    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/quant_model/Layer2_Relu_eightbit_reshape_dims_0.idx"),
            "Layer2/Relu_eightbit_reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "Layer2/Relu_eightbit_reshape_Layer2/zscore:0", 2);
    ctx.push(new ReshapeOp(), 
             { "Layer2/zscore:0", "Layer2/Relu_eightbit_reshape_dims:0" },
             { "Layer2/Relu_eightbit_reshape_Layer2/zscore:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/quant_model/Layer2_Relu_eightbit_reduction_dims_0.idx"),
            "Layer2/Relu_eightbit_reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "Layer2/Relu_eightbit_min_Layer2/zscore:0", 1);
    ctx.push(new MinOp(), 
             { "Layer2/Relu_eightbit_reshape_Layer2/zscore:0", "Layer2/Relu_eightbit_reduction_dims:0" },
             { "Layer2/Relu_eightbit_min_Layer2/zscore:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "Layer2/Relu_eightbit_max_Layer2/zscore:0", 1);
    ctx.push(new MaxOp(), 
             { "Layer2/Relu_eightbit_reshape_Layer2/zscore:0", "Layer2/Relu_eightbit_reduction_dims:0" },
             { "Layer2/Relu_eightbit_max_Layer2/zscore:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Layer2/Relu_eightbit_quantize_Layer2/zscore:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer2/Relu_eightbit_quantize_Layer2/zscore:1", 1);
    ctx.add(new RamTensor<float>({1}), "Layer2/Relu_eightbit_quantize_Layer2/zscore:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "Layer2/zscore:0",  "Layer2/Relu_eightbit_min_Layer2/zscore:0", "Layer2/Relu_eightbit_max_Layer2/zscore:0" },
             {  "Layer2/Relu_eightbit_quantize_Layer2/zscore:0",  "Layer2/Relu_eightbit_quantize_Layer2/zscore:1", "Layer2/Relu_eightbit_quantize_Layer2/zscore:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Layer2/Relu_eightbit_quantized:0", 1);
    ctx.add(new RamTensor<float>({1}), "Layer2/Relu_eightbit_quantized:1", 1);
    ctx.add(new RamTensor<float>({1}), "Layer2/Relu_eightbit_quantized:2", 1);
    ctx.push(new ReluOp<uint8_t, float, uint8_t>(), 
             { "Layer2/Relu_eightbit_quantize_Layer2/zscore:0", "Layer2/Relu_eightbit_quantize_Layer2/zscore:1", "Layer2/Relu_eightbit_quantize_Layer2/zscore:2" },
             { "Layer2/Relu_eightbit_quantized:0", "Layer2/Relu_eightbit_quantized:1", "Layer2/Relu_eightbit_quantized:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.ubyte_import("/fs/constants/quant_model/OuputLayer_Variable_quint8_const_0.idx"),
            "OuputLayer/Variable_quint8_const:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/OuputLayer_Variable_min_0.idx"),
            "OuputLayer/Variable_min:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/OuputLayer_Variable_max_0.idx"),
            "OuputLayer/Variable_max:0",
            1);
}
{
    ctx.add(new RamTensor<int>(), "OuputLayer/MatMul_eightbit_quantized_mat_mul:0", 2);
    ctx.add(new RamTensor<float>({1}), "OuputLayer/MatMul_eightbit_quantized_mat_mul:1", 2);
    ctx.add(new RamTensor<float>({1}), "OuputLayer/MatMul_eightbit_quantized_mat_mul:2", 2);
    ctx.push(new QntMatMulOp<uint8_t, uint8_t, int>(), 
             { "Layer2/Relu_eightbit_quantized:0", "Layer2/Relu_eightbit_quantized:1", "Layer2/Relu_eightbit_quantized:2", "OuputLayer/Variable_quint8_const:0", "OuputLayer/Variable_min:0",  "OuputLayer/Variable_max:0" },
             { "OuputLayer/MatMul_eightbit_quantized_mat_mul:0", "OuputLayer/MatMul_eightbit_quantized_mat_mul:1",  "OuputLayer/MatMul_eightbit_quantized_mat_mul:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "OuputLayer/MatMul_eightbit_requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "OuputLayer/MatMul_eightbit_requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "OuputLayer/MatMul_eightbit_quantized_mat_mul:0", "OuputLayer/MatMul_eightbit_quantized_mat_mul:1", "OuputLayer/MatMul_eightbit_quantized_mat_mul:2" },
             { "OuputLayer/MatMul_eightbit_requant_range:0", "OuputLayer/MatMul_eightbit_requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "OuputLayer/MatMul_eightbit_requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "OuputLayer/MatMul_eightbit_requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "OuputLayer/MatMul_eightbit_requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "OuputLayer/MatMul_eightbit_quantized_mat_mul:0", "OuputLayer/MatMul_eightbit_quantized_mat_mul:1", "OuputLayer/MatMul_eightbit_quantized_mat_mul:2", "OuputLayer/MatMul_eightbit_requant_range:0", "OuputLayer/MatMul_eightbit_requant_range:1" },
             { "OuputLayer/MatMul_eightbit_requantize:0", "OuputLayer/MatMul_eightbit_requantize:1", "OuputLayer/MatMul_eightbit_requantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>(), "OuputLayer/MatMul:0", 1);
    ctx.push(new DequantizeOp(), 
             { "OuputLayer/MatMul_eightbit_requantize:0", "OuputLayer/MatMul_eightbit_requantize:1", "OuputLayer/MatMul_eightbit_requantize:2" },
             { "OuputLayer/MatMul:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/quant_model/OuputLayer_Variable_1_0.idx"),
            "OuputLayer/Variable_1:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "OuputLayer/prediction:0", 1);
    ctx.push(new AddOp<float, float>(),
             { "OuputLayer/MatMul:0", "OuputLayer/Variable_1:0" }, 
             { "OuputLayer/prediction:0" });

    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/quant_model/Prediction_y_pred_dimension_0.idx"),
            "Prediction/y_pred/dimension:0",
            1);
}
{
    ctx.add(new RamTensor<int>(), "Prediction/y_pred:0");
    ctx.push(new ArgMaxOp<float, int>(), 
             { "OuputLayer/prediction:0", "Prediction/y_pred/dimension:0" },
             { "Prediction/y_pred:0" });
}
}