// Copyright 2019 TF.Text Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TENSORFLOW_TEXT_CORE_KERNELS_REGEX_SPLIT_H_
#define TENSORFLOW_TEXT_CORE_KERNELS_REGEX_SPLIT_H_

#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "re2/re2.h"
#include "tensorflow/core/framework/types.h"

namespace tensorflow {
namespace text {

void RegexSplit(const tstring& input, const RE2& re2, bool include_delimiter,
                const RE2& include_delim_regex,
                std::vector<absl::string_view>* tokens,
                std::vector<int64>* begin_offsets,
                std::vector<int64>* end_offsets);

}  // namespace text
}  // namespace tensorflow

#endif  // TENSORFLOW_TEXT_CORE_KERNELS_REGEX_SPLIT_H_
