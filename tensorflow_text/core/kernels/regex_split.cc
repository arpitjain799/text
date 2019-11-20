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

#include "tensorflow_text/core/kernels/regex_split.h"

#include <vector>

namespace tensorflow {
namespace text {

void RegexSplit(const tstring& input, const RE2& re2, bool include_delimiter,
                const RE2& include_delim_regex,
                std::vector<absl::string_view>* tokens,
                std::vector<int64>* begin_offsets,
                std::vector<int64>* end_offsets) {
  absl::string_view leftover(input.data());
  absl::string_view last_end = leftover;

  // Keep looking for split points until we have reached the end of the input.
  absl::string_view extracted_delim_token;
  while (RE2::FindAndConsume(&leftover, re2, &extracted_delim_token)) {
    absl::string_view token(last_end.data(),
                            extracted_delim_token.data() - last_end.data());
    bool has_non_empty_token = token.length() > 0;
    bool should_include_delim =
        include_delimiter && include_delim_regex.FullMatch(
                                 extracted_delim_token, include_delim_regex);
    last_end = leftover;

    // Mark the end of the previous token, only if there was something.
    if (has_non_empty_token) {
      tokens->push_back(token);
      // Mark the end of the last token
      begin_offsets->push_back(token.data() - input.data());
      end_offsets->push_back(token.data() + token.length() - input.data());
    }

    if (should_include_delim) {
      // If desired, include the deliminator as a token.
      tokens->push_back(extracted_delim_token);
      // Mark the end of the token at the end of the beginning of the delimiter.
      begin_offsets->push_back(extracted_delim_token.data() - input.data());
      end_offsets->push_back(extracted_delim_token.data() +
                             extracted_delim_token.length() - input.data());
    }
  }

  // Close the last token.
  if (!leftover.empty()) {
    tokens->push_back(leftover);
    begin_offsets->push_back(leftover.data() - input.data());
    end_offsets->push_back(leftover.data() + leftover.length() - input.data());
  }
}

}  // namespace text
}  // namespace tensorflow
