// kaldifeat/csrc/test_kaldifeat.cc
//
// Copyright (c)  2021  Xiaomi Corporation (authors: Fangjun Kuang)

#include "torch/torch.h"

static void TestPreemph() {
  torch::Tensor a = torch::arange(0, 12).reshape({3, 4}).to(torch::kFloat);

  torch::Tensor b =
      a.index({"...", torch::indexing::Slice(1, torch::indexing::None,
                                             torch::indexing::None)});

  torch::Tensor c = a.index({"...", torch::indexing::Slice(0, -1, 1)});

  a.index({"...", torch::indexing::Slice(1, torch::indexing::None,
                                         torch::indexing::None)}) =
      b - 0.97 * c;

  a.index({"...", 0}) *= 0.97;

  std::cout << a << "\n";
  std::cout << b << "\n";
  std::cout << "c: \n" << c << "\n";
  torch::Tensor d = b - 0.97 * c;
  std::cout << d << "\n";
}

static void TestPad() {
  torch::Tensor a = torch::arange(0, 6).reshape({2, 3}).to(torch::kFloat);
  torch::Tensor b = torch::nn::functional::pad(
      a, torch::nn::functional::PadFuncOptions({0, 3})
             .mode(torch::kConstant)
             .value(0));
  std::cout << a << "\n";
  std::cout << b << "\n";
}

int main() {
  TestPad();
  return 0;
}