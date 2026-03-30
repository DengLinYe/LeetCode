# LeetCode Log

> - 先以《面试经典150题》开始，每日两题预计五月中结束，此后题目再议。
> - 题目后的`*`个数表示难度，一般我能做出等效最优解的题目，不视为难题，即 *；而若能解出但不是最优，则 **；若无法解出，则 \*\*\*。特别地，如果做到了等效最优解，但是相对不够好，则 \*/\*\*
> - `@`被认为是重点题目

## 零、一些配置

- **通用模板设置**：

  1. 在 VSCode 中，点击左下角齿轮 -> **（用户）代码片段 (User Snippets)**。

  2. 搜索并选择 `cpp`。

  3. 将以下 JSON 代码粘贴进去：

     ```json
     {
       "LeetCode Template": {
         "prefix": "lcc",
         "body": [
           "#include <iostream>",
           "#include <vector>",
           "#include <string>",
           "#include <algorithm>",
           "#include <unordered_map>",
           "#include <queue>",
           "",
           "using namespace std;",
           "",
           "int main() {",
           "    ios::sync_with_stdio(false);",
           "    cin.tie(nullptr);",
           "    $0",
           "    return 0;",
           "}"
         ],
         "description": "快速生成力扣/机试基础模板"
       }
     }
     ```

     > - 运行时由于没有自动刷新，所以需要手动在键盘上按 `Ctrl + Z`，然后敲击回车

- **格式化风格**
  1. 在 VSCode 中按 `Ctrl + ,` 打开设置。
  2. 在搜索框输入 `fallback style`。
  3. 找到 **C_Cpp: Clang_format_fallback Style**。
  4. 将默认的 `Visual Studio` 改为 `Google` 或 `LLVM`



## 一、数组 / 字符串

### 1. 合并两个有序数组*

#### 1.1 题目

给你两个按 **非递减顺序** 排列的整数数组 `nums1` 和 `nums2`，另有两个整数 `m` 和 `n` ，分别表示 `nums1` 和 `nums2` 中的元素数目。

请你 **合并** `nums2` 到 `nums1` 中，使合并后的数组同样按 **非递减顺序** 排列。

**注意：**最终，合并后数组不应由函数返回，而是存储在数组 `nums1` 中。为了应对这种情况，`nums1` 的初始长度为 `m + n`，其中前 `m` 个元素表示应合并的元素，后 `n` 个元素为 `0` ，应忽略。`nums2` 的长度为 `n` 。

 

**示例 1：**

```
输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
```

**示例 2：**

```
输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。
```

**示例 3：**

```
输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。
```

 

**提示：**

- `nums1.length == m + n`
- `nums2.length == n`
- `0 <= m, n <= 200`
- `1 <= m + n <= 200`
- `-109 <= nums1[i], nums2[j] <= 109`

 

**进阶：**你可以设计实现一个时间复杂度为 `O(m + n)` 的算法解决此问题吗？



#### 1.2 解法

时间复杂度 $O(m + n)$；空间复杂度 $O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int k = m + n - 1;
    m--;
    n--;

    // 倒序比较，无需开辟新数组
    while (m >= 0 && n >= 0) {
      if (nums1[m] < nums2[n]) {
        nums1[k] = nums2[n];
        n--;
      } else {
        nums1[k] = nums1[m];
        m--;
      }
      k--;
    }

    // 若nums1有剩，则无需移动
    while (n >= 0) {
      nums1[k] = nums2[n];
      k--;
      n--;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m, n;
  while (cin >> m >> n) {
    vector<int> nums1(m + n);
    for (int i = 0; i < m + n; ++i) {
      cin >> nums1[i];
    }

    vector<int> nums2(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums2[i];
    }

    Solution().merge(nums1, m, nums2, n);

    cout << "[";
    for (int i = 0; i < m + n; ++i) {
      cout << nums1[i] << (i == m + n - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}
```



#### 1.3 解析

这题比较简单，我这个解法已经是理论最优解，算是开门红。

简单地来看看其他的解法吧：

1. 暴力破解

   ```cpp
   #include <vector>
   #include <algorithm>
   
   using namespace std;
   
   class Solution {
   public:
       void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
           for (int i = 0; i < n; ++i) {
               nums1[m + i] = nums2[i];
           }
           sort(nums1.begin(), nums1.end());
       }
   };
   ```

   > 直接使用sort，复杂度为 `O(log(m+n))`

2. 另辟数组

   ```cpp
   #include <vector>
   
   using namespace std;
   
   class Solution {
   public:
       void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
           vector<int> nums1_copy(nums1.begin(), nums1.begin() + m);
           int p1 = 0;
           int p2 = 0;
           int p = 0;
           
           while (p1 < m && p2 < n) {
               if (nums1_copy[p1] <= nums2[p2]) {
                   nums1[p++] = nums1_copy[p1++];
               } else {
                   nums1[p++] = nums2[p2++];
               }
           }
           
           while (p1 < m) {
               nums1[p++] = nums1_copy[p1++];
           }
           
           while (p2 < n) {
               nums1[p++] = nums2[p2++];
           }
       }
   };
   ```

   > 空间复杂度 `O(m)`



### 2. 移除元素*

#### 2.1 题目

给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素。元素的顺序可能发生改变。然后返回 `nums` 中与 `val` 不同的元素的数量。

假设 `nums` 中不等于 `val` 的元素数量为 `k`，要通过此题，您需要执行以下操作：

- 更改 `nums` 数组，使 `nums` 的前 `k` 个元素包含不等于 `val` 的元素。`nums` 的其余元素和 `nums` 的大小并不重要。
- 返回 `k`。

**用户评测：**

评测机将使用以下代码测试您的解决方案：

```
int[] nums = [...]; // 输入数组
int val = ...; // 要移除的值
int[] expectedNums = [...]; // 长度正确的预期答案。
                            // 它以不等于 val 的值排序。

int k = removeElement(nums, val); // 调用你的实现

assert k == expectedNums.length;
sort(nums, 0, k); // 排序 nums 的前 k 个元素
for (int i = 0; i < actualLength; i++) {
    assert nums[i] == expectedNums[i];
}
```

如果所有的断言都通过，你的解决方案将会 **通过**。

 

**示例 1：**

```
输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2,_,_]
解释：你的函数应该返回 k = 2, 并且 nums 中的前两个元素均为 2。
你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。
```

**示例 2：**

```
输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3,_,_,_]
解释：你的函数应该返回 k = 5，并且 nums 中的前五个元素为 0,0,1,3,4。
注意这五个元素可以任意顺序返回。
你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。
```

 

**提示：**

- `0 <= nums.length <= 100`
- `0 <= nums[i] <= 50`
- `0 <= val <= 100`



#### 2.2 解法

**时间复杂度**：$O(n)$，**空间复杂度**：$O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeElement(vector<int>& nums, int val) {
    int n = nums.size(), k = 0, i = 0;
    while (i + k < n) {
      if (nums[i] == val) {
        swap(nums[i], nums[n - k - 1]);
        k++;
      }

      // 避免交换到val
      if (nums[i] != val) {
        i++;
      }
    }

    return i;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, val;
  while (cin >> n >> val) {
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    Solution obj;
    int k = obj.removeElement(nums, val);

    sort(nums.begin(), nums.begin() + k);

    cout << k << ", nums = [";
    for (int i = 0; i < k; ++i) {
      cout << nums[i] << (i == k - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}
```

> 优化写法（左右指针/双指针）：方法类似，但是更有逻辑一些。
>
> ```cpp
> class Solution {
> public:
>     int removeElement(vector<int>& nums, int val) {
>         int left = 0;
>         int right = nums.size();
>         while (left < right) {
>             if (nums[left] == val) {
>                 nums[left] = nums[right - 1];
>                 right--;
>             } else {
>                 left++;
>             }
>         }
>         return left;
>     }
> };
> ```



#### 2.3 解析

这道题同样比较简单，我的解法是等效最优解，在某些情况比标准解更快。

简单的看看标准解：

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
        }
        return slow;
    }
};
```

> 固定时间复杂度为$O(n)$，快慢指针方法，直接覆盖慢指针，无需交换。



### 3. 删除有序数组中的重复项*

#### 3.1 题目

给你一个 **非严格递增排列** 的数组 `nums` ，请你**[ 原地](http://baike.baidu.com/item/原地算法)** 删除重复出现的元素，使每个元素 **只出现一次** ，返回删除后数组的新长度。元素的 **相对顺序** 应该保持 **一致** 。然后返回 `nums` 中唯一元素的个数。

考虑 `nums` 的唯一元素的数量为 `k`。去重后，返回唯一元素的数量 `k`。

`nums` 的前 `k` 个元素应包含 **排序后** 的唯一数字。下标 `k - 1` 之后的剩余元素可以忽略。

**判题标准:**

系统会用下面的代码来测试你的题解:

```
int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的期望答案

int k = removeDuplicates(nums); // 调用

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
```

如果所有断言都通过，那么您的题解将被 **通过**。

 

**示例 1：**

```
输入：nums = [1,1,2]
输出：2, nums = [1,2,_]
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
```

**示例 2：**

```
输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4,_,_,_,_,_]
解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。
```

 

**提示：**

- `1 <= nums.length <= 3 * 104`
- `-100 <= nums[i] <= 100`
- `nums` 已按 **非递减** 顺序排列。



#### 3.2 解法

**时间复杂度**：$O(n)$，**空间复杂度**：$O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int base = 0, check = 0, n = nums.size();
    while (check < n) {
      if (nums[base] == nums[check]) {
        nums[base] = nums[check];
        check++;
      } else {
        base++;
        nums[base] = nums[check];
        check++;
      }
    }

    return base + 1;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    Solution obj;
    int k = obj.removeDuplicates(nums);

    cout << k << ", nums = [";
    for (int i = 0; i < k; ++i) {
      cout << nums[i] << (i == k - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}
```

> 当时为了避免算法起步失败，让相等时也赋值，这是不必要的；此外还有一些小的冗余，优化如下：
>
> ```cpp
> class Solution {
> public:
>     int removeDuplicates(vector<int>& nums) {
>         int base = 0;
>         
>        // 快指针直接1开始，不需要考虑起步问题；check一定会++，所以直接使用for循环 
>         for (int check = 1; check < nums.size(); check++) {
>             if (nums[check] != nums[base]) {
>                 base++;
>                 nums[base] = nums[check];
>             }
>         }
>         
>         return base + 1;
>     }
> };
> ```



#### 3.3 解析

我的解法写得有点丑陋，但是也算是等效最优解。此外，可以看看别的一些办法：

1. K位去重模板（有序）

   ```cpp
   class Solution {
   public:
       int removeDuplicates(vector<int>& nums) {
           int slow = 0;
           
        	// 当不再等于时，慢指针才++   
           for (int x : nums) {
               if (slow < 1 || nums[slow - 1] != x) {
                   nums[slow] = x;
                   slow++;
               }
           }
           
           return slow;
       }
   };
   ```

2. STL库

   ```cpp
   #include <algorithm>
   
   class Solution {
   public:
       int removeDuplicates(vector<int>& nums) {
        	// 返回的是整理后的数组的末尾迭代器，减去begin()就是长度
           return unique(nums.begin(), nums.end()) - nums.begin();
       }
   };
   ```



### 4. 删除有序数组中的重复项II*

#### 4.1 题目

给你一个有序数组 `nums` ，请你**[ 原地](http://baike.baidu.com/item/原地算法)** 删除重复出现的元素，使得出现次数超过两次的元素**只出现两次** ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 **[原地 ](https://baike.baidu.com/item/原地算法)修改输入数组** 并在使用 O(1) 额外空间的条件下完成。

 

**说明：**

为什么返回数值是整数，但输出的答案是数组呢？

请注意，输入数组是以**「引用」**方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

```
// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

 

**示例 1：**

```
输入：nums = [1,1,1,2,2,3]
输出：5, nums = [1,1,2,2,3]
解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3。 不需要考虑数组中超出新长度后面的元素。
```

**示例 2：**

```
输入：nums = [0,0,1,1,1,1,2,3,3]
输出：7, nums = [0,0,1,1,2,3,3]
解释：函数应返回新长度 length = 7, 并且原数组的前七个元素被修改为 0, 0, 1, 1, 2, 3, 3。不需要考虑数组中超出新长度后面的元素。
```

 

**提示：**

- `1 <= nums.length <= 3 * 104`
- `-104 <= nums[i] <= 104`
- `nums` 已按升序排列



#### 4.2 解法

时间复杂度 $O(n)$，空间复杂度 $O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int base = 0, check = 1, n = nums.size();
    bool flag = true;

    if (n <= 1) {
      return n;
    }

    while (check < n) {
      if (nums[base] == nums[check]) {
        if (flag) {
          base++;
          flag = false;
        }
        nums[base] = nums[check];
        check++;
      } else {
        base++;
        nums[base] = nums[check];
        flag = true;
        check++;
      }
    }

    return base + 1;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    Solution obj;
    int k = obj.removeDuplicates(nums);

    cout << k << ", nums = [";
    for (int i = 0; i < k; ++i) {
      cout << nums[i] << (i == k - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}
```

> 这是基于上一题改的，同样有一定的冗余问题：
>
> ```cpp
> class Solution {
> public:
>     int removeDuplicates(vector<int>& nums) {
>         int n = nums.size();
>         if (n <= 2) return n;
> 
>         int base = 0;
>         bool flag = true; 
> 
>         for (int check = 1; check < n; check++) {
>             if (nums[base] == nums[check]) {
>                 if (flag) {
>                     base++;
>                     nums[base] = nums[check];
>                     flag = false;
>                 }
>             } else {
>                 base++;
>                 nums[base] = nums[check];
>                 flag = true;
>             }
>         }
>         
>         return base + 1;
>     }
> };
> ```
>
> 



#### 4.3 解析

这道题同样地是等效最优解，由于是基于上一题解法改的，也同样有点丑陋。这里就没什么其他解法了，上一题给的通用K模板，在已经是很好的做法。



### 5. 多数元素**

#### 5.1 题目

给定一个大小为 `n` 的数组 `nums` ，返回其中的多数元素。多数元素是指在数组中出现次数 **大于** `⌊ n/2 ⌋` 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

 

**示例 1：**

```
输入：nums = [3,2,3]
输出：3
```

**示例 2：**

```
输入：nums = [2,2,1,1,1,2,2]
输出：2
```

 

**提示：**

- `n == nums.length`
- `1 <= n <= 5 * 10^4`
- `-10^9 <= nums[i] <= 10^9`
- 输入保证数组中一定有一个多数元素。

 

**进阶：**尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。



#### 5.2 解法

**时间复杂度**：$O(n)$，**空间复杂度**：$O(n)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    unordered_map<int, int> freq;
    int max = 0, maxNum = 0;

    for (auto x : nums) {
      if (++freq[x] > max) {
        max = freq[x];
        maxNum = x;
      }
    }

    return maxNum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    Solution obj;
    int k = obj.majorityElement(nums);

    cout << k;
  }

  return 0;
}
```

> 我们不必要找出max，只要频率满足条件即可
>
> ```cpp
> #include <unordered_map>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int majorityElement(vector<int>& nums) {
>         unordered_map<int, int> freq;
>         int target = nums.size() / 2;
> 
>         for (int x : nums) {
>             if (++freq[x] > target) {
>                 return x;
>             }
>         }
> 
>         return -1;
>     }
> };
> ```



#### 5.3 解析

这次并未找到等效最优解，要么是内存大了，要么就是时间慢了，来看看别的解法：

1. 排序法

   ```cpp
   // 内存严格达标，但是时间超出
   #include <algorithm>
   #include <vector>
   
   using namespace std;
   
   class Solution {
   public:
       int majorityElement(vector<int>& nums) {
           sort(nums.begin(), nums.end());
           return nums[nums.size() / 2];
       }
   };
   ```

2. **Boyer-Moore 投票算法**

   **时间复杂度**：$O(n)$，**空间复杂度**：$O(1)$。这个方法很巧妙，核心在于利用了多数元素频次比数组中其他任何元素频次之和还要大，也即选取一个candidate，如果遇到等值数即++，遇到非等值即--，当count为0时重选candidate，如此能保证多数元素与所有其他元素“一换一”后还能至少存活一个（count=1），即得结果。

   ```cpp
   #include <vector>
   
   using namespace std;
   
   class Solution {
   public:
       int majorityElement(vector<int>& nums) {
           int candidate = 0;
           int count = 0;
   
           for (int x : nums) {
               if (count == 0) {
                   candidate = x;
               }
               if (x == candidate) {
                   count++;
               } else {
                   count--;
               }
           }
   
           return candidate;
       }
   };
   ```

   

### 6. 轮转数组**

#### 6.1 题目

给定一个整数数组 `nums`，将数组中的元素向右轮转 `k` 个位置，其中 `k` 是非负数。

 

**示例 1:**

```
输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右轮转 1 步: [7,1,2,3,4,5,6]
向右轮转 2 步: [6,7,1,2,3,4,5]
向右轮转 3 步: [5,6,7,1,2,3,4]
```

**示例 2:**

```
输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]
解释: 
向右轮转 1 步: [99,-1,-100,3]
向右轮转 2 步: [3,99,-1,-100]
```

 

**提示：**

- `1 <= nums.length <= 105`
- `-231 <= nums[i] <= 231 - 1`
- `0 <= k <= 105`

 

**进阶：**

- 尽可能想出更多的解决方案，至少有 **三种** 不同的方法可以解决这个问题。
- 你可以使用空间复杂度为 `O(1)` 的 **原地** 算法解决这个问题吗？



#### 6.2 解法

1. 时间复杂度为 $O(n \times k)$，空间复杂度为 $O(1)$
2. 时间复杂度 $O(n)$，空间复杂度 $O(n)$
3. 错误解法

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % int(n);
    if (k == 0) return;

    rotate3(nums, k, n);
  }

  void rotate1(vector<int>& nums, int k, int n) {
    for (int i = 0; i < k; i++) {
      for (int j = n - 1; j > 0; j--) {
        swap(nums[j], nums[j - 1]);
      }
    }
  }

  void rotate2(vector<int>& nums, int k, int n) {
    vector<int> rotateNum(n);

    for (int i = 0; i < n; i++) {
      rotateNum[(i + k) % n] = nums[i];
    }

    nums = rotateNum;
  }

  void rotate3(vector<int>& nums, int k, int n) {
    for (int i = 0; i < n / k; i++) {
      for (int j = 0; j < k; j++) {
        swap(nums[i * k + j], nums[n - k + j]);
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  while (cin >> n) {
    cin >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    Solution obj;
    obj.rotate(nums, k);

    cout << "nums = [";
    for (int i = 0; i < nums.size(); ++i) {
      cout << nums[i] << (i == nums.size() - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}
```



#### 6.3 解析

花了很长的时间，仍无法改好rorate3，未来的思路可能是较为复杂的递归，理论能能够达到$O(1)$空间复杂度，但是递归本身也需要相当的空间（拆解成循环或可实现，但是过于复杂）。

1. **三次翻转**：

   一个很显著的特征就是平移，但是要原地地实现平移就是难点。我们可以三次翻转，即先翻转一次，发现前后两段位置对了，但是顺序不对，再各自独立翻转一次即可：

   > 观察输入 `[1, 2, 3, 4, 5, 6, 7]` 和输出 `[5, 6, 7, 1, 2, 3, 4]`。
   >
   > 可以发现，数组其实被分成了两段：
   >
   > - **尾部段** `[5, 6, 7]`（长度为 $k$）：它们整体平移到了最前面。
   > - **首部段** `[1, 2, 3, 4]`（长度为 $n-k$）：它们整体平移到了后面。
   >
   > 如果我们直接将整个数组首尾翻转，变成 `[7, 6, 5, 4, 3, 2, 1]`。
   >
   > 此时，原本在尾部的元素确实跑到前面去了，原本在前面的元素也跑到后面去了。唯一的问题是，这两段内部的元素顺序是逆序的。
   >
   > 因此，我们只需要将前 $k$ 个元素再翻转一次，把后面的 $n-k$ 个元素也翻转一次，就能完美负负得正，恢复原来的相对顺序。

   ```cpp
   #include <vector>
   #include <algorithm>
   
   using namespace std;
   
   class Solution {
   public:
       void rotate(vector<int>& nums, int k) {
           int n = nums.size();
           k = k % n;
           
           reverse(nums.begin(), nums.end());
           reverse(nums.begin(), nums.begin() + k);
           reverse(nums.begin() + k, nums.end());
       }
   };
   ```

2. 环状替换：

   仅了解。

   ```cpp
   #include <vector>
   #include <numeric>
   
   using namespace std;
   
   class Solution {
   public:
       void rotate(vector<int>& nums, int k) {
           int n = nums.size();
           k = k % n;
           if (k == 0) return;
   
           int count = gcd(k, n);
           
           for (int start = 0; start < count; ++start) {
               int current = start;
               int prev = nums[start];
               
               do {
                   int next = (current + k) % n;
                   int temp = nums[next];
                   nums[next] = prev;
                   prev = temp;
                   current = next;
               } while (start != current);
           }
       }
   };
   ```




### 7. 买卖股票的最佳时机*

#### 7.1 题目

给定一个数组 `prices` ，它的第 `i` 个元素 `prices[i]` 表示一支给定股票第 `i` 天的价格。

你只能选择 **某一天** 买入这只股票，并选择在 **未来的某一个不同的日子** 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 `0` 。

 

**示例 1：**

```
输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
```

**示例 2：**

```
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
```

 

**提示：**

- `1 <= prices.length <= 105`
- `0 <= prices[i] <= 104`



#### 7.2 解法

时间复杂度 **O(n)**，空间复杂度为 **O(1)**

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int n = prices.size(), sum = 0, b = 0;

    for (int i = 1; i < n; i++) {
      int profit = prices[i] - prices[i - 1];
      if (b > 0) {
        b += profit;
      } else {
        b = profit;
      }

      sum = max(b, sum);
    }

    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i];
    }

    Solution obj;
    int profit = obj.maxProfit(p);

    cout << profit;
  }
  return 0;
}
```

> 一些写法上的优化：（实际上差不多）
>
> ```cpp
> class Solution {
> public:
>     int maxProfit(vector<int>& prices) {
>         int n = prices.size();
>         int sum = 0, b = 0;
> 
>         for (int i = 1; i < n; i++) {
>             int profit = prices[i] - prices[i - 1];
>             b = max(profit, b + profit);
>             sum = max(b, sum);
>         }
> 
>         return sum;
>     }
> };
> ```



#### 7.3 解析

我的解法达到了等效最优解，本质上是利用了动态规划中的最大字段和问题的解法。事实上还有一些别的想法：

1. 贪心算法

   算是这道题的标准解法，重点在于相对最小值，即：若在`i`出卖出，那么此前若是在最低点买入的，则必然是该天卖出的最大利润情况。这样的想法把找最小值和比较利润最大值融合，同样是 **O(n)**的时间复杂度。

   ```cpp
   class Solution {
   public:
       int maxProfit(vector<int>& prices) {
           int minPrice = 1e9;
           int maxProf = 0;
   
           for (int price : prices) {
               minPrice = min(minPrice, price);
               maxProf = max(maxProf, price - minPrice);
           }
   
           return maxProf;
       }
   };
   ```

2. 状态机动态规划

   每一天，我们只有两种状态：**持有股票**（状态 1）或 **不持有股票**（状态 0）。

   - 今天**不持有**股票的最大收益，等于：昨天也不持有，或者昨天持有但今天卖掉了，两者取最大。
   - 今天**持有**股票的最大收益，等于：昨天就持有，或者昨天不持有但今天买入了，两者取最大（因为只能交易一次，所以今天买入的收益就是 `-prices[i]`）。

   这类题关键在于状态的确定与比较，即：

   ```cpp
   class Solution {
   public:
       int maxProfit(vector<int>& prices) {
           int n = prices.size();
           if (n == 0) return 0;
   
           int dp_i_0 = 0;
           int dp_i_1 = -prices[0];
   
           for (int i = 1; i < n; i++) {
               dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
               dp_i_1 = max(dp_i_1, -prices[i]);
           }
   
           return dp_i_0;
       }
   };
   ```



### 8. 买卖股票的最佳时机II*

#### 8.1 题目

给你一个整数数组 `prices` ，其中 `prices[i]` 表示某支股票第 `i` 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 **最多** 只能持有 **一股** 股票。然而，你可以在 **同一天** 多次买卖该股票，但要确保你持有的股票不超过一股。

返回 *你能获得的 **最大** 利润* 。

 

**示例 1：**

```
输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3。
最大总利润为 4 + 3 = 7 。
```

**示例 2：**

```
输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
最大总利润为 4 。
```

**示例 3：**

```
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0。
```

 

**提示：**

- `1 <= prices.length <= 3 * 104`
- `0 <= prices[i] <= 104`



#### 8.2 解法

时间复杂度 $O(n)$，空间复杂度 $O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int n = prices.size(), sum = 0;

    for (int i = 1; i < n; i++) {
      int profit = prices[i] - prices[i - 1];
      if (profit > 0) {
        sum += profit;
      }
    }

    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i];
    }

    Solution obj;
    int profit = obj.maxProfit(p);

    cout << profit;
  }
  return 0;
}
```

> 也是写法上的：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int maxProfit(vector<int>& prices) {
>         int n = prices.size(), sum = 0;
> 
>         for (int i = 1; i < n; i++) {
>             sum += max(0, prices[i] - prices[i - 1]);
>         }
> 
>         return sum;
>     }
> };
> ```



#### 8.3 解析

上一题的思路在此发挥了巨大的作用，其本质上是贪心算法，将全局问题拆解为了最小粒度的局部问题。

再看看上一题的DP状态机在这题的改进：

```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        int dp_i_0 = 0;
        int dp_i_1 = -prices[0];

        for (int i = 1; i < n; i++) {
            // 区别在于这次的买入有基础资金dp_i_0，也就是昨天没有持有股票时的利润
            int temp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, temp - prices[i]);
        }

        return dp_i_0;
    }
};
```



### 9. 跳跃游戏*

#### 9.1 题目

给你一个非负整数数组 `nums` ，你最初位于数组的 **第一个下标** 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

```
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
```

**示例 2：**

```
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
```

 

**提示：**

- `1 <= nums.length <= 104`
- `0 <= nums[i] <= 105`

 

#### 9.2 解法

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canJump(vector<int>& nums) {
    int n = nums.size(), canReach = 0;
    for (int i = 0; i < n; i++) {
      if (canReach < i) {
        return false;
      } else {
        canReach = max(canReach, i + nums[i]);
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    Solution obj;
    bool canJump = obj.canJump(nums);
    cout << canJump;
  }

  return 0;
}
```

> 可以加入一个提前终止的机制，即若途中canReach即可达到末尾，可以终止：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool canJump(vector<int>& nums) {
>         int n = nums.size(), canReach = 0;
>         
>         for (int i = 0; i < n; i++) {
>             if (canReach < i) {
>                 return false;
>             }
>             
>             canReach = max(canReach, i + nums[i]);
>             
>             // 若直接可达末位，终止
>             if (canReach >= n - 1) {
>                 return true;
>             }
>         }
> 
>         return true;
>     }
> };
> ```



#### 9.3 解析

同样达到了等效最优解，来看看另外两种比较经典的解法：

1. 逆向贪心

   与本解同为贪心，不过是逆向跑的：如果目的地是最后一个点，那么逆向遍历，如果遇到的点能够到达上一个目的地，那么新的目的地就变成了该点，直到结束如果目的地移动到了最开始的点，那么就成功。

   ```cpp
   class Solution {
   public:
       bool canJump(vector<int>& nums) {
           int n = nums.size();
           int destination = n - 1;
           
           for (int i = n - 2; i >= 0; i--) {
               if (i + nums[i] >= destination) {
                   destination = i;
               }
           }
           
           return destination == 0;
       }
   };
   ```

2. 动态规划

   **“在想不到贪心策略时，万物皆可 DP。”**

   同样来看状态：定义 `dp[i]` 表示“能否到达下标 `i`”。 如果要到达下标 `i`，那么在它前面的所有点 `j` 中，必须存在至少一个点满足两个条件：第一，点 `j` 本身是可达的（`dp[j] == true`）；第二，从点 `j` 起跳的最大距离能覆盖到 `i`（`j + nums[j] >= i`）。

   但是这种解法的时间复杂度是 $O(n^2)$，很可能超时。

   ```cpp
   class Solution {
   public:
       bool canJump(vector<int>& nums) {
           int n = nums.size();
           vector<bool> dp(n, false);
           dp[0] = true;
           
           for (int i = 1; i < n; i++) {
               for (int j = 0; j < i; j++) {
                   if (dp[j] && j + nums[j] >= i) {
                       dp[i] = true;
                       break;
                   }
               }
           }
           
           return dp[n - 1];
       }
   };
   ```



### 10. 跳跃游戏II**

#### 10.1 题目

给定一个长度为 `n` 的 **0 索引**整数数组 `nums`。初始位置在下标 0。

每个元素 `nums[i]` 表示从索引 `i` 向后跳转的最大长度。换句话说，如果你在索引 `i` 处，你可以跳转到任意 `(i + j)` 处：

- `0 <= j <= nums[i]` 且
- `i + j < n`

返回到达 `n - 1` 的最小跳跃次数。测试用例保证可以到达 `n - 1`。

 

**示例 1:**

```
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
```

**示例 2:**

```
输入: nums = [2,3,0,1,4]
输出: 2
```

 

**提示:**

- `1 <= nums.length <= 104`
- `0 <= nums[i] <= 1000`
- 题目保证可以到达 `n - 1`



#### 10.2 解法

时间复杂度接近 $O(n!)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int minTimes = 10000;

  int jump(vector<int>& nums) {
    if (nums.size() == 1) {
      return 0;
    }

    canReach(nums, nums.size() - 1, -1);

    return minTimes;
  }

  void canReach(vector<int>& nums, int k, int times) {
    // cout << "enter pos:" << k << ", and now:" << times << endl;
    times++;
    if (times > minTimes) return;

    for (int i = k - 1; i >= 0; i--) {
      if (i + nums[i] >= k) {
        // cout << "in " << k << ", reach: " << i << ", and now: " << times
        //      << endl;
        if (i == 0) {
          minTimes = min(minTimes, times + 1);
          return;
        } else {
          canReach(nums, i, times);
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    Solution obj;
    int jumpTimes = obj.jump(nums);
    cout << jumpTimes;
  }

  return 0;
}
```

> 可以从开始往后搜索，而不是从后往前。这样的话搜索算法的复杂度能降下来到时间复杂度是 $O(n^2)$，空间复杂度是 $O(1)$。
>
> ```cpp
> #include <vector>
> #include <algorithm>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int jump(vector<int>& nums) {
>         int position = nums.size() - 1;
>         int steps = 0;
>         
>         while (position > 0) {
>             for (int i = 0; i < position; i++) {
>                 if (i + nums[i] >= position) {
>                     position = i;
>                     steps++;
>                     break;
>                 }
>             }
>         }
>         
>         return steps;
>     }
> };
> ```



#### 10.3 解析

很遗憾未能找到最优解，优化后的搜索算法仍然是  $O(n^2)$级别的。看看其他办法吧，最优解本质上就是我上一题的优化解法，我也曾这样想过，可惜当时未能理解其本质：

```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int maxReach = 0;
        int end = 0;
        int steps = 0;
        
        for (int i = 0; i < nums.size() - 1; i++) {
            maxReach = max(maxReach, i + nums[i]);
            
            if (i == end) {
                end = maxReach;
                steps++;
            }
        }
        
        return steps;
    }
}
```

其核心在于steps++的时机上，也即当我们未到达当前最大覆盖范围的边界时，始终在上一次step+1次跳跃的可控范围内，不需要真的加一；而若到达了边界，则需要加一落实新的一次跳跃以达到该边界；若超出，则无法到达末尾。这是上一题思路的更深入扩充，也就是把能够到达时候的情况讨论得更加深入了。



### 11. H 指数*

#### 11.1 题目

给你一个整数数组 `citations` ，其中 `citations[i]` 表示研究者的第 `i` 篇论文被引用的次数。计算并返回该研究者的 **`h` 指数**。

根据维基百科上 [h 指数的定义](https://baike.baidu.com/item/h-index/3991452?fr=aladdin)：`h` 代表“高引用次数” ，一名科研人员的 `h` **指数** 是指他（她）至少发表了 `h` 篇论文，并且 **至少** 有 `h` 篇论文被引用次数大于等于 `h` 。如果 `h` 有多种可能的值，**`h` 指数** 是其中最大的那个。

 

**示例 1：**

```
输入：citations = [3,0,6,1,5]
输出：3 
解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
     由于研究者有 3 篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用 不多于 3 次，所以她的 h 指数是 3。
```

**示例 2：**

```
输入：citations = [1,3,1]
输出：1
```

 

**提示：**

- `n == citations.length`
- `1 <= n <= 5000`
- `0 <= citations[i] <= 1000`



#### 11.2 解法

**时间复杂度**：$O(n)$，**空间复杂度**：$O(n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int hIndex(vector<int>& citations) {
    int n = citations.size(), h = 0;
    unordered_map<int, int> passby;

    for (int x : citations) {
      if (x > h) {
        passby[x]++;
        if (h >= h + 1 - passby[h]) {
          passby[h]--;
        } else {
          h = h + 1 - passby[h];
        }
      }
    }

    return h;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    Solution obj;
    int h = obj.hIndex(nums);
    cout << h;
  }

  return 0;
}
```

> 那个判断条件`h >= h + 1 - passby[h]`事实上能移项简化，有：
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int hIndex(vector<int>& citations) {
>         int h = 0;
>         int n = citations.size();
>         vector<int> passby(1001, 0); 
> 
>         for (int x : citations) {
>             if (x > h) {
>                 passby[min(x, 1000)]++;
>                 if (passby[h] > 0) {
>                     passby[h]--;
>                 } else {
>                     h++;
>                 }
>             }
>         }
> 
>         return h;
>     }
> };
> ```



#### 11.3 解析

我的方法达到了等效最优解，本质上是空间换时间，核心是h++之后，会被踢出h内的论文，正确地处理它们即可解出本题。

当然，如果追求空间复杂度最小，直接排序就能做；然后还有一种等效最优解是桶排序。

1. 直接排序法

   ```cpp
   #include <vector>
   #include <algorithm>
   #include <iostream>
   
   using namespace std;
   
   class Solution {
   public:
       int hIndex(vector<int>& citations) {
           // 直接使用内置排序即可
           sort(citations.begin(), citations.end(), greater<int>());
           int h = 0;
           
           for (int i = 0; i < citations.size(); i++) {
               if (citations[i] > h) {
                   h++;
               } else {
                   break;
               }
           }
           
           return h;
       }
   };
   ```

2. 计数排序/桶排序

   本质上还是排序，但是用了最快的桶排序（$O(n)$），核心是注意到提示中citations的上限只是1000。

   ```cpp
   #include <vector>
   #include <algorithm>
   #include <iostream>
   
   using namespace std;
   
   class Solution {
   public:
       int hIndex(vector<int>& citations) {
           int n = citations.size();
           vector<int> count(n + 1, 0);
   
           for (int c : citations) {
               if (c >= n) {
                   count[n]++;
               } else {
                   count[c]++;
               }
           }
   
           int total = 0;
           for (int i = n; i >= 0; i--) {
               total += count[i];
               if (total >= i) {
                   return i;
               }
           }
   
           return 0;
       }
   };
   ```



### 12. O(1) 时间插入、删除和获取随机元素*

#### 12.1 题目

实现`RandomizedSet` 类：

- `RandomizedSet()` 初始化 `RandomizedSet` 对象
- `bool insert(int val)` 当元素 `val` 不存在时，向集合中插入该项，并返回 `true` ；否则，返回 `false` 。
- `bool remove(int val)` 当元素 `val` 存在时，从集合中移除该项，并返回 `true` ；否则，返回 `false` 。
- `int getRandom()` 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 **相同的概率** 被返回。

你必须实现类的所有函数，并满足每个函数的 **平均** 时间复杂度为 `O(1)` 。

 

**示例：**

```
输入
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
输出
[null, true, false, true, 2, true, false, 2]

解释
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
randomizedSet.remove(2); // 返回 false ，表示集合中不存在 2 。
randomizedSet.insert(2); // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
randomizedSet.remove(1); // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
randomizedSet.insert(2); // 2 已在集合中，所以返回 false 。
randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
```

 

**提示：**

- `-231 <= val <= 231 - 1`
- 最多调用 `insert`、`remove` 和 `getRandom` 函数 `2 * ``105` 次
- 在调用 `getRandom` 方法时，数据结构中 **至少存在一个** 元素。



#### 12.2 解法



```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

static std::random_device rd;
static std::mt19937 gen(rd());

class RandomizedSet {
 public:
  unordered_map<int, int> index;
  vector<int> set;

  RandomizedSet() { set.push_back(-1); }

  bool insert(int val) {
    if (index[val] == 0) {
      set.push_back(val);
      index[val] = set.size() - 1;
      return true;
    } else {
      return false;
    }
  }

  bool remove(int val) {
    if (index[val] == 0) {
      return false;
    } else {
      index[set.back()] = index[val];
      set[index[val]] = set.back();
      set.pop_back();
      index[val] = 0;
      return true;
    }
  }

  int getRandom() {
    uniform_int_distribution<> dis(1, set.size() - 1);

    return set[dis(gen)];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    RandomizedSet* obj = nullptr;
    cout << "[";
    for (int i = 0; i < n; ++i) {
      string op;
      cin >> op;
      if (op == "RandomizedSet") {
        obj = new RandomizedSet();
        cout << "null";
      } else if (op == "insert") {
        int val;
        cin >> val;
        cout << (obj->insert(val) ? "true" : "false");
      } else if (op == "remove") {
        int val;
        cin >> val;
        cout << (obj->remove(val) ? "true" : "false");
      } else if (op == "getRandom") {
        cout << obj->getRandom();
      }

      if (i < n - 1) cout << ",";
    }
    cout << "]\n";

    delete obj;
  }

  return 0;
}
```



#### 12.3 解析

同样也算等效最优解，但是直接把index设为0，会让该index仍然存在（只是值为0），会导致空间无法释放，所以优化一下就是：

```cpp
static std::random_device rd;
static std::mt19937 gen(rd());

class RandomizedSet {
public:
    unordered_map<int, int> index;
    vector<int> set;

    RandomizedSet() {}

    bool insert(int val) {
        if (index.count(val)) {
            return false;
        }
        set.push_back(val);
        index[val] = set.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (!index.count(val)) {
            return false;
        }
        int lastElement = set.back();
        int idx = index[val];

        set[idx] = lastElement;
        index[lastElement] = idx;

        set.pop_back();
        index.erase(val); // 就是用了erase
        return true;
    }

    int getRandom() {
        uniform_int_distribution<> dis(0, set.size() - 1);
        return set[dis(gen)];
    }
};
```



### 13. 除自身以外数组的乘积*

#### 13.1 题目

给你一个整数数组 `nums`，返回 数组 `answer` ，其中 `answer[i]` 等于 `nums` 中除了 `nums[i]` 之外其余各元素的乘积 。

题目数据 **保证** 数组 `nums`之中任意元素的全部前缀元素和后缀的乘积都在 **32 位** 整数范围内。

请 **不要使用除法，**且在 `O(n)` 时间复杂度内完成此题。

 

**示例 1:**

```
输入: nums = [1,2,3,4]
输出: [24,12,8,6]
```

**示例 2:**

```
输入: nums = [-1,1,0,-3,3]
输出: [0,0,9,0,0]
```

 

**提示：**

- `2 <= nums.length <= 105`
- `-30 <= nums[i] <= 30`
- 输入 **保证** 数组 `answer[i]` 在 **32 位** 整数范围内

 

**进阶：**你可以在 `O(1)` 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组 **不被视为** 额外空间。）



#### 13.2 解法

时间复杂度$O(n)$，空间复杂度$O(1)$（除输出数组）

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size(), mul = 1;
    vector<int> out(n, 1);

    for (int i = 0; i < n - 1; i++) {
      mul *= nums[i];
      out[i + 1] *= mul;
    }

    mul = 1;
    for (int i = n - 1; i > 0; i--) {
      mul *= nums[i];
      out[i - 1] *= mul;
    }

    return out;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    Solution obj;
    vector<int> out = obj.productExceptSelf(nums);

    cout << "[";
    for (int i = 0; i < n; i++) {
      cout << out[i] << (i == n - 1 ? " " : ", ");
    }
    cout << "]\n";
  }

  return 0;
}
```

> 可以再简化一点
>
> ```cpp
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<int> productExceptSelf(vector<int>& nums) {
>         int n = nums.size();
>         vector<int> out(n, 1);
> 
>         for (int i = 1; i < n; i++) {
>             // 在前面可以暂时不用变量，但是没什么区别
>             out[i] = out[i - 1] * nums[i - 1];
>         }
> 
>         int R = 1;
>         for (int i = n - 1; i >= 0; i--) {
>             out[i] = out[i] * R;
>             R *= nums[i];
>         }
> 
>         return out;
>     }
> };
> ```



#### 13.3 解析

这次不存在太多的等效最优解，我这个可能就是唯一的最优解。另有一个思路，也就是我的解的基础版，就是用数组去存前缀积以及后缀积，但是这样额外空间相当的大。





### 14. 加油站*/**

#### 14.1 题目

在一条环路上有 `n` 个加油站，其中第 `i` 个加油站有汽油 `gas[i]` 升。

你有一辆油箱容量无限的的汽车，从第 `i` 个加油站开往第 `i+1` 个加油站需要消耗汽油 `cost[i]` 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 `gas` 和 `cost` ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 `-1` 。如果存在解，则 **保证** 它是 **唯一** 的。

 

**示例 1:**

```
输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2] 
输出: 3
解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
```

**示例 2:**

```
输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。
```

 

**提示:**

- `n == gas.length == cost.length`
- `1 <= n <= 105`
- `0 <= gas[i], cost[i] <= 104`
- 输入保证答案唯一。



#### 14.2 解法

时间复杂度是 `O(n)`，空间复杂度是 `O(1)`。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size(), sum = 0, b = 0, bSt = 0, st = 0;

    for (int i = 0; i < 2 * n; i++) {
      int index = i % n;
      if (i - bSt >= n) break;

      int k = gas[index] - cost[index];
      if (b > 0) {
        b += k;
      } else {
        b = k;
        bSt = index;
      }

      if (b > sum) {
        sum = b;
        st = bSt;
      }
    }

    sum = 0;
    for (int i = st; i < st + n; i++) {
      int index = i % n;
      sum += gas[index] - cost[index];
      if (sum < 0) {
        return -1;
      }
    }

    return st;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> gas(n), cost(n);
    for (int i = 0; i < n; i++) {
      cin >> gas[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> cost[i];
    }

    Solution obj;
    int st = obj.canCompleteCircuit(gas, cost);
    cout << st;
  }

  return 0;
}
```



#### 14.3 解析

则也算等效最优解，但是稍微差了些。这道题我想了比较久，最后是抓到了“唯一解”，进而想到最优解一定是唯一解，从而把最大子段和的思路挪到了这里。但是事实上并不需要最大富余油量的最优解，可以把这个贪心思路更简化一些，这道题的关键在两处：

1. 全局上，如果总和小于零，必然没有解；反之有解。
2. 局部上，**如果$\sum(A,B)<0$，那么A、B之间的任意一个点都不能作为起点**，这稍微有点绕，其实是迭代条件的必然结果（如果n到n+1时和为负，则立即淘汰，所以从A到n所剩油量必为非负，而若非负都无法进入到B，那么A到B的任意一点都不行）。

明白这一点，这道题还是比较简单的：

```cpp
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total_sum = 0;
        int current_sum = 0;
        int start = 0;

        for (int i = 0; i < gas.size(); i++) {
            int diff = gas[i] - cost[i];
            total_sum += diff;
            current_sum += diff;

            if (current_sum < 0) {
                start = i + 1;
                current_sum = 0;
            }
        }

        if (total_sum < 0) {
            return -1;
        }

        return start;
    }
};
```



### 15. 分发糖果*/**

#### 15.1 题目

`n` 个孩子站成一排。给你一个整数数组 `ratings` 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

- 每个孩子至少分配到 `1` 个糖果。
- 相邻两个孩子中，评分更高的那个会获得更多的糖果。

请你给每个孩子分发糖果，计算并返回需要准备的 **最少糖果数目** 。

 

**示例 1：**

```
输入：ratings = [1,0,2]
输出：5
解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
```

**示例 2：**

```
输入：ratings = [1,2,2]
输出：4
解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。
```

 

**提示：**

- `n == ratings.length`
- `1 <= n <= 2 * 104`
- `0 <= ratings[i] <= 2 * 104`



#### 15.2 解法

时间复杂度是 `O(n)`，空间复杂度是 `O(1)`。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int candy(vector<int>& ratings) {
    int n = ratings.size(), sum = 0, flag = 0, base = 1, tempSum = 0;
    if (n == 1) return 1;
    ratings.push_back(ratings.back());
    for (int i = 1; i < n + 1; i++) {
      int sub = ratings[i] - ratings[i - 1];
      int cat = sub * flag;
      if (cat > 0) {
        tempSum++;
      } else if (cat < 0) {
        if (flag < 0) {
          sum += max(0, base - tempSum - 2);
          base = 1;
        }
        sum += (2 * base + tempSum + (flag - 1) * (-1)) * (tempSum + 1) / 2;
        if (flag > 0) base += tempSum + 1;
        flag *= -1;
        tempSum = 0;
      } else {
        if (sub == 0) {
          if (flag != 0) {
            if (flag < 0) {
              sum += max(0, base - tempSum - 2);
              base = 1;
            }
            if (flag < 0) base = 1;
            sum += (2 * base + tempSum + 1) * (tempSum + 2) / 2;
            tempSum = 0;
            flag *= 0;
          } else {
            sum++;
            base = 1;
          }
        } else {
          if (sub > 0) {
            flag = 1;
          } else {
            flag = -1;
          }
        }
      }
    }
    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> ratings;
    for (int i = 0; i < n; i++) {
      cin >> ratings[i];
    }

    Solution obj;
    int sum = obj.candy(ratings);
    cout << sum;
  }

  return 0;
}
```

> 这个思路从一开始就有点问题，后面限于沉没成本打了一些补丁，最终也是正确的，效果上也不错，但是可以优化：
>
> ```cpp
> class Solution {
> public:
>     int candy(vector<int>& ratings) {
>         int n = ratings.size();
>         if (n == 0) return 0;
>         
>         int totalCandies = 1;
>         int up = 1;
>         int down = 0;
>         int peak = 1;
>         
>         for (int i = 1; i < n; i++) {
>             if (ratings[i] > ratings[i - 1]) {
>                 down = 0;
>                 up++;
>                 peak = up;
>                 totalCandies += up;
>             } else if (ratings[i] == ratings[i - 1]) {
>                 down = 0;
>                 up = 1;
>                 peak = 1;
>                 totalCandies += 1;
>             } else {
>                 up = 1;
>                 down++;
>                 totalCandies += down;
>                 if (peak <= down) {
>                     totalCandies++;
>                 }
>             }
>         }
>         
>         return totalCandies;
>     }
> };
> ```
>
> 这个思路就清晰很多了，和我的方法本质上是一样的。事实上从左到右的一次遍历只会有三种情况：
>
> 1. 更大：那么应该++
> 2. 不变：直接重置为1
> 3. 更小：加下坡长度（down）；如果长度超过了下降前的值（peak，或者说是这个孩子的糖果已经要小于1了），那就总数额外加1（并不需要把前面的都加，只要peak对应的孩子加即可）



#### 15.3 解析

我虽然也是等效最优解，但是并不好看。优化之后的思路其实逻辑已经很清晰了，但是两次遍历的贪心算法相对更加标准、易懂且稳定：既然题目要求“相邻两个孩子评分更高的孩子会获得更多的糖果”，这句话其实包含两个维度的约束：

1. **左规则**：如果右边的孩子评分比左边高，右边孩子的糖果必须比左边多。
2. **右规则**：如果左边的孩子评分比右边高，左边孩子的糖果必须比右边多。

我们不要试图同时满足这两个规则，那样大脑会过载。 先从左往右扫一遍：每个人初始先发 1 个糖。如果右边比左边分数高，右边的糖果就等于左边加 1。这保证了所有**上坡**都符合规矩。 再从右往左扫一遍：如果左边比右边分数高，且左边的糖果还没有右边多，就把左边的糖果拔高到右边加 1。这保证了所有**下坡**也符合规矩。所以有：

```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> candies(n, 1);
        
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        
        int total = candies[n - 1];
        
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
            total += candies[i];
        }
        
        return total;
    }
};
```



### 16. 接雨水*

#### 16.1 题目

给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

**示例 1：**

![img](./assets/rainwatertrap.png)

```
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
```

**示例 2：**

```
输入：height = [4,2,0,3,2,5]
输出：9
```

 

**提示：**

- `n == height.length`
- `1 <= n <= 2 * 104`
- `0 <= height[i] <= 105`



#### 16.2 解法

时间复杂度$O(n)$，空间复杂度为 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int trap(vector<int>& height) {
    int st = 0, n = height.size(), peak = 0, peakSum = 0, rain = 0;
    for (int i = 0; i < n; i++) {
      if (height[i] >= peak) {
        rain += peak * (i - st - 1) - peakSum;
        st = i;
        peakSum = 0;
        peak = height[i];
      } else {
        peakSum += height[i];
      }
    }

    peak = 0;
    peakSum = 0;
    int ed = n - 1;
    for (int i = n - 1; i >= st; i--) {
      if (height[i] >= peak) {
        rain += peak * (ed - i - 1) - peakSum;
        ed = i;
        peakSum = 0;
        peak = height[i];
      } else {
        peakSum += height[i];
      }
    }

    return rain;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> height(n);
    for (int i = 0; i < n; i++) {
      cin >> height[i];
    }

    Solution obj;
    int rain = obj.trap(height);
    cout << rain;
  }

  return 0;
}
```



#### 16.3 解析

同样是等效最优解，我们只需要找到最大值，分别从其两边向它遍历即可，理论最优可以达到一次遍历，但是期望是1.5次。不过还有很多其他解法：

1. **双指针**

   对于任意一个位置 `i`（仅`i`本身，不考虑其他位置），它能接多少水，完全取决于它**左边最高的柱子**和**右边最高的柱子**中更矮的那个，即：
   $$
   \text{水} = \min(\text{左最高}, \text{右最高}) - \text{当前高度}
   $$
   设有两个指针right与left分别在两边开始向内收紧：

   - 如果 `height[left] < height[right]`，这意味着左边较低，此时右边即使有再高的柱子也无济于事，制约水位的“短板”一定在左边。所以我们放心地用 `left_max` 结算左边当前位置的水，然后左指针右移。
   - 反之，制约水位的短板在右边，结算右侧并左移。

   这种解法不仅是 $O(1)$​ 空间，而且只遍历数组一次。

   ```cpp
   #include <vector>
   
   using namespace std;
   
   class Solution {
   public:
       int trap(vector<int>& height) {
           int left = 0, right = height.size() - 1;
           int left_max = 0, right_max = 0;
           int water = 0;
   
           while (left < right) {
               if (height[left] < height[right]) {
                   if (height[left] >= left_max) {
                       left_max = height[left];
                   } else {
                       water += left_max - height[left];
                   }
                   left++;
               } else {
                   if (height[right] >= right_max) {
                       right_max = height[right];
                   } else {
                       water += right_max - height[right];
                   }
                   right--;
               }
           }
           return water;
       }
   };
   ```

2. **单调栈**

   这个办法其实我也开了个头，但是没有深入，也就是按行横着算水。我们用一个栈来维护一个单调递减的高度序列。一旦遇到一个比栈顶高的柱子，说明我们遇到了一个“坑”的右边界，而栈里的元素就是坑底和左边界。 此时将坑底弹出，通过当前的柱子（右边界）和新的栈顶（左边界）计算出坑的宽度和有效高度，得出一层横向的水量。接着继续对比，直到栈重新变得单调递减。 这种解法的空间复杂度退化到了 $O(n)$。

   > 并不存在维护栈单调性的额外时间花销，事实上我最开始是因为误解了这一点导致没有继续深入。元素按遍历循序入栈，而当遇到更高的柱子时，会立即触发结算，从而一直到栈中没有比它更小的元素，则暂置栈顶；若更小，则直接入栈，因此始终保持单调性。

   ```cpp
   #include <stack>
   #include <vector>
   #include <algorithm>
   
   using namespace std;
   
   class Solution {
   public:
       int trap(vector<int>& height) {
           int water = 0;
           stack<int> st;
   
           for (int i = 0; i < height.size(); i++) {
               while (!st.empty() && height[i] > height[st.top()]) {
                   int top = st.top();
                   st.pop();
   
                   if (st.empty()) break;
   
                   int distance = i - st.top() - 1;
                   int bounded_height = min(height[i], height[st.top()]) - height[top];
                   water += distance * bounded_height;
               }
               st.push(i);
           }
           return water;
       }
   };
   ```




### 17. 罗马数字转整数*

#### 17.1 题目

罗马数字包含以下七种字符: `I`， `V`， `X`， `L`，`C`，`D` 和 `M`。

```
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

例如， 罗马数字 `2` 写做 `II` ，即为两个并列的 1 。`12` 写做 `XII` ，即为 `X` + `II` 。 `27` 写做 `XXVII`, 即为 `XX` + `V` + `II` 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 `IIII`，而是 `IV`。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 `IX`。这个特殊的规则只适用于以下六种情况：

- `I` 可以放在 `V` (5) 和 `X` (10) 的左边，来表示 4 和 9。
- `X` 可以放在 `L` (50) 和 `C` (100) 的左边，来表示 40 和 90。 
- `C` 可以放在 `D` (500) 和 `M` (1000) 的左边，来表示 400 和 900。

给定一个罗马数字，将其转换成整数。

 

**示例 1:**

```
输入: s = "III"
输出: 3
```

**示例 2:**

```
输入: s = "IV"
输出: 4
```

**示例 3:**

```
输入: s = "IX"
输出: 9
```

**示例 4:**

```
输入: s = "LVIII"
输出: 58
解释: L = 50, V= 5, III = 3.
```

**示例 5:**

```
输入: s = "MCMXCIV"
输出: 1994
解释: M = 1000, CM = 900, XC = 90, IV = 4.
```

 

**提示：**

- `1 <= s.length <= 15`
- `s` 仅含字符 `('I', 'V', 'X', 'L', 'C', 'D', 'M')`
- 题目数据保证 `s` 是一个有效的罗马数字，且表示整数在范围 `[1, 3999]` 内
- 题目所给测试用例皆符合罗马数字书写规则，不会出现跨位等情况。
- IL 和 IM 这样的例子并不符合题目要求，49 应该写作 XLIX，999 应该写作 CMXCIX 。
- 关于罗马数字的详尽书写规则，可以参考 [罗马数字 - 百度百科](https://baike.baidu.com/item/罗马数字/772296)。



#### 17.2 解法

**时间复杂度**：$O(n)$，**空间复杂度**：$O(1)$

```
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int romanToInt(string s) {
    int n = s.size(), sum = 0;
    unordered_map<string, int> value;
    value["I"] = 1;
    value["IV"] = 4;
    value["V"] = 5;
    value["IX"] = 9;
    value["X"] = 10;
    value["XL"] = 40;
    value["L"] = 50;
    value["XC"] = 90;
    value["C"] = 100;
    value["CD"] = 400;
    value["D"] = 500;
    value["CM"] = 900;
    value["M"] = 1000;

    for (int i = 0; i < n; i++) {
      switch (s[i]) {
        case 'I':
          if (i != n - 1 && (s[i + 1] == 'V' || s[i + 1] == 'X')) {
            sum += value[s.substr(i, 2)];
            i++;
          } else {
            sum += value[s.substr(i, 1)];
          }
          break;
        case 'X':
          if (i != n - 1 && (s[i + 1] == 'L' || s[i + 1] == 'C')) {
            sum += value[s.substr(i, 2)];
            i++;
          } else {
            sum += value[s.substr(i, 1)];
          }
          break;
        case 'C':
          if (i != n - 1 && (s[i + 1] == 'D' || s[i + 1] == 'M')) {
            sum += value[s.substr(i, 2)];
            i++;
          } else {
            sum += value[s.substr(i, 1)];
          }
          break;
        default:
          sum += value[s.substr(i, 1)];
          break;
      }
    }

    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      Solution obj;
      cout << obj.romanToInt(s) << "\n";
    }
  }

  return 0;
}
```

> `.substr`和双字符的映射表会消耗很多的空间与时间，适当简化：
>
> ```cpp
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int romanToInt(string s) {
>         int sum = 0;
>         int n = s.size();
>         
>         for (int i = 0; i < n; i++) {
>             int current = getValue(s[i]);
>             
>             // 用对应数值的递增性质替代字符比较
>             if (i < n - 1 && current < getValue(s[i + 1])) {
>                 sum -= current;
>             } else {
>                 sum += current;
>             }
>         }
>         
>         return sum;
>     }
> 
> // 用一个函数替代映射（因为是固定的映射表，并没有变动需求）
> private:
>     int getValue(char ch) {
>         switch (ch) {
>             case 'I': return 1;
>             case 'V': return 5;
>             case 'X': return 10;
>             case 'L': return 50;
>             case 'C': return 100;
>             case 'D': return 500;
>             case 'M': return 1000;
>             default: return 0;
>         }
>     }
> };
> ```



#### 17.3 解析

同样达到了最优解的标准。但是这里忽略了一个重要的特性，即：一个字符代表的数值如果比左边的小，那么它就是要被减去的，否则就是正的原值。如果考虑到这一点，那么逆向遍历会更加简单一些。



### 18. 整数转罗马数字*

#### 18.1 题目

七个不同的符号代表罗马数字，其值如下：

| 符号 | 值   |
| ---- | ---- |
| I    | 1    |
| V    | 5    |
| X    | 10   |
| L    | 50   |
| C    | 100  |
| D    | 500  |
| M    | 1000 |

罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：

- 如果该值不是以 4 或 9 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
- 如果该值以 4 或 9 开头，使用 **减法形式**，表示从以下符号中减去一个符号，例如 4 是 5 (`V`) 减 1 (`I`): `IV` ，9 是 10 (`X`) 减 1 (`I`)：`IX`。仅使用以下减法形式：4 (`IV`)，9 (`IX`)，40 (`XL`)，90 (`XC`)，400 (`CD`) 和 900 (`CM`)。
- 只有 10 的次方（`I`, `X`, `C`, `M`）最多可以连续附加 3 次以代表 10 的倍数。你不能多次附加 5 (`V`)，50 (`L`) 或 500 (`D`)。如果需要将符号附加4次，请使用 **减法形式**。

给定一个整数，将其转换为罗马数字。

 

**示例 1：**

**输入：**num = 3749

**输出：** "MMMDCCXLIX"

**解释：**

```
3000 = MMM 由于 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC 由于 500 (D) + 100 (C) + 100 (C)
  40 = XL 由于 50 (L) 减 10 (X)
   9 = IX 由于 10 (X) 减 1 (I)
注意：49 不是 50 (L) 减 1 (I) 因为转换是基于小数位
```

**示例 2：**

**输入：**num = 58

**输出：**"LVIII"

**解释：**

```
50 = L
 8 = VIII
```

**示例 3：**

**输入：**num = 1994

**输出：**"MCMXCIV"

**解释：**

```
1000 = M
 900 = CM
  90 = XC
   4 = IV
```

 

**提示：**

- `1 <= num <= 3999`



#### 18.2 解法

时间复杂度 $O(1)$，空间复杂度也是 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string intToRoman(int num) {
    int base = 1000;
    string roman;
    while (base > 0) {
      int k = num / base;
      num = num % base;

      if (k == 0) {
        base /= 10;
        continue;
      }

      if (k == 9 || k == 4) {
        roman = roman + Tran(base) + Tran((k + 1) * base);
      } else if (k >= 5) {
        roman += Tran(5 * base);
        for (int i = 5; i < k; i++) {
          roman += Tran(base);
        }
      } else {
        for (int i = 0; i < k; i++) {
          roman += Tran(base);
        }
      }

      base /= 10;
    }

    return roman;
  }

 private:
  string Tran(int a) {
    switch (a) {
      case 1:
        return "I";
      case 5:
        return "V";
      case 10:
        return "X";
      case 50:
        return "L";
      case 100:
        return "C";
      case 500:
        return "D";
      case 1000:
        return "M";
      default:
        return "0";
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int num;
  cin >> num;

  Solution obj;
  string result = obj.intToRoman(num);

  for (int i = 0; i < result.size(); i++) {
    cout << result[i];
  }

  return 0;
}
```

> 一些写法上可以优化：
>
> ```cpp
> #include <iostream>
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     string intToRoman(int num) {
>         int base = 1000;
>         string roman;
>         roman.reserve(16);
> 
>         while (base > 0) {
>             int k = num / base;
>             num = num % base;
> 
>             if (k == 0) {
>                 base /= 10;
>                 continue;
>             }
> 
>             if (k == 9 || k == 4) {
>                 // 直接+=避免产生临时对象
>                 roman += Tran(base);
>                 roman += Tran((k + 1) * base);
>             } else if (k >= 5) {
>                 roman += Tran(5 * base);
>                 for (int i = 5; i < k; i++) {
>                     roman += Tran(base);
>                 }
>             } else {
>                 for (int i = 0; i < k; i++) {
>                     roman += Tran(base);
>                 }
>             }
> 
>             base /= 10;
>         }
> 
>         return roman;
>     }
> 
> private:
>     // 返回常字符串引用，减少空间花销
>     const string& Tran(int a) {
>         static const string I = "I", V = "V", X = "X", L = "L", C = "C", D = "D", M = "M", Z = "";
>         switch (a) {
>             case 1: return I;
>             case 5: return V;
>             case 10: return X;
>             case 50: return L;
>             case 100: return C;
>             case 500: return D;
>             case 1000: return M;
>             default: return Z;
>         }
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     int num;
>     while (cin >> num) {
>         Solution obj;
>         // 直接cout
>         cout << obj.intToRoman(num) << "\n";
>     }
> 
>     return 0;
> }
> ```



#### 18.3 解析

也达到了最优解，但是还有一些别的比较不错的解法：

1. 贪心：

   类似于找零，比较好理解：

   ```cpp
   class Solution {
   public:
       string intToRoman(int num) {
           const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
           const string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
           
           string roman;
           for (int i = 0; i < 13; i++) {
               while (num >= values[i]) {
                   num -= values[i];
                   roman += symbols[i];
               }
           }
           
           return roman;
       }
   };
   ```

2. 面向答案：

   直接暴力破解（限值小于4000）

   ```cpp
   class Solution {
   public:
       string intToRoman(int num) {
           const string M[] = {"", "M", "MM", "MMM"};
           const string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
           const string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
           const string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
           
           return M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10] + I[num % 10];
       }
   };
   ```

   

### 19. 最后一个单词的长度*/**

#### 19.1 题目

给你一个字符串 `s`，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中 **最后一个** 单词的长度。

**单词** 是指仅由字母组成、不包含任何空格字符的最大子字符串。

 

**示例 1：**

```
输入：s = "Hello World"
输出：5
解释：最后一个单词是“World”，长度为 5。
```

**示例 2：**

```
输入：s = "   fly me   to   the moon  "
输出：4
解释：最后一个单词是“moon”，长度为 4。
```

**示例 3：**

```
输入：s = "luffy is still joyboy"
输出：6
解释：最后一个单词是长度为 6 的“joyboy”。
```

 

**提示：**

- `1 <= s.length <= 104`
- `s` 仅有英文字母和空格 `' '` 组成
- `s` 中至少存在一个单词



#### 19.2 解法

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLastWord(string s) {
    int n = s.size(), lastLen = 0, state = 0;

    for (int i = 0; i < n; i++) {
      if (state == 0 && s[i] != ' ') {
        state++;
        lastLen = 1;
      } else if (state == 1) {
        if (s[i] != ' ') {
          lastLen++;
        } else {
          state--;
        }
      }
    }

    return lastLen;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.lengthOfLastWord(s);

  return 0;
}
```



#### 19.3 解析

严格来说，我这个办法不算最优解，因为最优解能够达到$O(1)$级别。事实上所谓最后一个，只需要倒着找就行了：

```cpp
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        int len = 0;
        int i = n - 1;

        while (i >= 0 && s[i] == ' ') {
            i--;
        }

        while (i >= 0 && s[i] != ' ') {
            len++;
            i--;
        }

        return len;
    }
};
```

或者直接用STL库的`find_last_not_of`

```cpp
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        size_t end = s.find_last_not_of(' ');
        
        if (end == string::npos) {
            return 0;
        }
        
        size_t start = s.find_last_of(' ', end);
        
        if (start == string::npos) {
            return end + 1;
        }
        
        return end - start;
    }
};
```



### 20. 最长公共前缀*

#### 20.1 题目

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 `""`。

 

**示例 1：**

```
输入：strs = ["flower","flow","flight"]
输出："fl"
```

**示例 2：**

```
输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
```

 

**提示：**

- `1 <= strs.length <= 200`
- `0 <= strs[i].length <= 200`
- `strs[i]` 如果非空，则仅由小写英文字母组成



#### 20.2 解法

时间复杂度 $O(S)$，其中 $S$ 是所有字符串的字符总数。空间复杂度 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    int n = strs.size();
    if (n == 0) return "";

    int k = strs[0].size();
    for (int i = 1; i < n; i++) {
      k = prefixFetch(strs[0], strs[i], k);
      if (k == 0) break;
    }

    return strs[0].substr(0, k);
  }

 private:
  int prefixFetch(string& a, string& b, int k) {
    int newK = 0;
    for (int i = 0; i < k; i++) {
      if (a[i] - b[i] == 0) {
        newK++;
      } else {
        break;
      }
    }

    return newK;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  if (!(cin >> n)) return 0;
  cin.ignore();

  vector<string> strs(n);
  for (int i = 0; i < n; i++) {
    getline(cin, strs[i]);
  }

  Solution obj;
  cout << obj.longestCommonPrefix(strs);

  return 0;
}
```

> 存在越界隐患：即若后续单词长度没有当前公共前缀长度长时，发生越界。
>
> ```cpp
> #include <iostream>
> #include <string>
> #include <vector>
> #include <algorithm>
> 
> using namespace std;
> 
> class Solution {
> public:
>     string longestCommonPrefix(vector<string>& strs) {
>         if (strs.empty()) return "";
> 
>         int k = strs[0].size();
>         
>         for (int i = 1; i < strs.size(); i++) {
>             // 取最小长度为边界
>             int limit = min(k, static_cast<int>(strs[i].size()));
>             k = 0;
>             
>             // 用while简化写法
>             while (k < limit && strs[0][k] == strs[i][k]) {
>                 k++;
>             }
>             
>             if (k == 0) break;
>         }
> 
>         return strs[0].substr(0, k);
>     }
> };
> ```



#### 20.3 解析

算是等效最优解吧，毕竟这个的时间复杂度事实上不好计算。另外还有两种思路，都挺好理解：

1. 纵向对比法

   不同于我的横向比较，纵向比较是对n个字符串一个个字符地比：

   ```cpp
   class Solution {
   public:
       string longestCommonPrefix(vector<string>& strs) {
           if (strs.empty()) return "";
   
           for (int i = 0; i < strs[0].size(); i++) {
               char c = strs[0][i];
               for (int j = 1; j < strs.size(); j++) {
                   if (i == strs[j].size() || strs[j][i] != c) {
                       return strs[0].substr(0, i);
                   }
               }
           }
   
           return strs[0];
       }
   };
   ```

2. 排序法

   时间复杂度较高。

   ```cpp
   class Solution {
   public:
       string longestCommonPrefix(vector<string>& strs) {
           if (strs.empty()) return "";
   
           sort(strs.begin(), strs.end());
   
           string first = strs.front();
           string last = strs.back();
           int k = 0;
           int limit = min(first.size(), last.size());
   
           while (k < limit && first[k] == last[k]) {
               k++;
           }
   
           return first.substr(0, k);
       }
   };
   ```




### 21. 反转字符串中的单词*

#### 21.1 题目

给你一个字符串 `s` ，请你反转字符串中 **单词** 的顺序。

**单词** 是由非空格字符组成的字符串。`s` 中使用至少一个空格将字符串中的 **单词** 分隔开。

返回 **单词** 顺序颠倒且 **单词** 之间用单个空格连接的结果字符串。

**注意：**输入字符串 `s`中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

 

**示例 1：**

```
输入：s = "the sky is blue"
输出："blue is sky the"
```

**示例 2：**

```
输入：s = "  hello world  "
输出："world hello"
解释：反转后的字符串中不能存在前导空格和尾随空格。
```

**示例 3：**

```
输入：s = "a good   example"
输出："example good a"
解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
```

 

**提示：**

- `1 <= s.length <= 104`
- `s` 包含英文大小写字母、数字和空格 `' '`
- `s` 中 **至少存在一个** 单词

 

**进阶：**如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用 `O(1)` 额外空间复杂度的 **原地** 解法。



#### 21.2 解法

时间复杂度 $O(n)$，空间复杂度 $O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string reverseWords(string s) {
    int n = s.size();
    for (int i = 0; i < n / 2; i++) {
      int temp = s[i];
      s[i] = s[n - i - 1];
      s[n - i - 1] = temp;
    }

    int k = 0, state = 0, lastStart = 0;
    s.push_back(' ');
    for (int i = 0; i <= n; i++) {
      if (state == 0 && s[i] != ' ') {
        lastStart = k;
        s[k++] = s[i];
        state++;
      } else if (state == 1) {
        if (s[i] == ' ') {
          state--;
          int d = lastStart + k;
          for (int j = lastStart; j < d / 2; j++) {
            int temp = s[j];
            s[j] = s[d - j - 1];
            s[d - j - 1] = temp;
          }
        }

        s[k++] = s[i];
      }
    }
    s.resize(k - 1);

    return s;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.reverseWords(s);

  return 0;
}
```

> 有一个`reverse`函数能够直接使用：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     string reverseWords(string s) {
>         reverse(s.begin(), s.end());
> 
>         int n = s.size();
>         int slow = 0;
> 
>         // 思路类似，但是简化了很多，也是一个个单词走的（while就是走单词），fast是原数组指针，slow是新数组指针（当然它们物理上是同一个数组）
>         for (int fast = 0; fast < n; fast++) {
>             if (s[fast] != ' ') {
>                 if (slow != 0) {
>                     s[slow++] = ' ';
>                 }
> 
>                 int start = slow;
>                 while (fast < n && s[fast] != ' ') {
>                     s[slow++] = s[fast++];
>                 }
> 
>                 reverse(s.begin() + start, s.begin() + slow);
>             }
>         }
>         
>         s.resize(slow);
>         return s;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     string s;
>     while (getline(cin, s)) {
>         Solution obj;
>         cout << obj.reverseWords(s) << "\n";
>     }
> 
>     return 0;
> }
> ```



#### 21.3 解析

已经是最优解，似乎没有什么等效的情况。此外还有一种空间 $O(n)$ 复杂度的写法：

```cpp
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        istringstream iss(s);
        string word; //新单词
        string result = "";	//额外数组存结果

        while (iss >> word) { // iss >> word类似cin，自动忽略空格（理解成用cin输入即可）
            if (result.empty()) {//开头处理
                result = word;
            } else {
                result = word + " " + result;
            }
        }

        return result;
    }
};
```



### 22. Z 字形变换*

#### 22.1 题目

将一个给定字符串 `s` 根据给定的行数 `numRows` ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 `"PAYPALISHIRING"` 行数为 `3` 时，排列如下：

```
P   A   H   N
A P L S I I G
Y   I   R
```

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如：`"PAHNAPLSIIGYIR"`。

请你实现这个将字符串进行指定行数变换的函数：

```
string convert(string s, int numRows);
```

 

**示例 1：**

```
输入：s = "PAYPALISHIRING", numRows = 3
输出："PAHNAPLSIIGYIR"
```

**示例 2：**

```
输入：s = "PAYPALISHIRING", numRows = 4
输出："PINALSIGYAHRPI"
解释：
P     I    N
A   L S  I G
Y A   H R
P     I
```

**示例 3：**

```
输入：s = "A", numRows = 1
输出："A"
```

 

**提示：**

- `1 <= s.length <= 1000`
- `s` 由英文字母（小写和大写）、`','` 和 `'.'` 组成
- `1 <= numRows <= 1000`



#### 22.2 解法

时间复杂度达到了 $O(n)$，空间复杂度为 $O(1)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string convert(string s, int numRows) {
    if (numRows == 1) return s;

    int n = s.size(), base = numRows * 2 - 2, f = 0, k = 0;
    string result;

    while (f < numRows && k < n) {
      bool flag = true;

      for (int i = f; i < n;) {
        result += s[i];
        k++;
        if (k >= n) break;

        int weight = base - f * 2;
        if (flag) {
          if (weight == 0) weight = base;
          i += weight;
        } else {
          if (weight == base) weight = 0;
          i += base - weight;
        }

        flag = !flag;
      }

      f++;
    }

    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  int n;
  cin >> n;

  Solution obj;
  cout << obj.convert(s, n);

  return 0;
}
```

> k的判断是冗余的；然后其实只有中间行才有特殊的斜线部分，这一点可以处理得更加简洁：
>
> ```cpp
> #include <iostream>
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     string convert(string s, int numRows) {
>         if (numRows == 1 || numRows >= s.size()) {
>             return s;
>         }
> 
>         string result;
>         int n = s.size();
>         int cycleLen = 2 * numRows - 2;
> 
>         for (int i = 0; i < numRows; i++) {
>             for (int j = 0; j + i < n; j += cycleLen) {
>                 result += s[j + i];
>                 
>                 if (i != 0 && i != numRows - 1 && j + cycleLen - i < n) {
>                     result += s[j + cycleLen - i];
>                 }
>             }
>         }
> 
>         return result;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     string s;
>     int n;
>     
>     while (cin >> s >> n) {
>         Solution obj;
>         cout << obj.convert(s, n) << "\n";
>     }
> 
>     return 0;
> }
> ```



#### 22.3 解析

同样是最优解，但是也可以按题目的说法直接模拟：

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || numRows >= s.size()) {
            return s;
        }

        vector<string> rows(min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[curRow] += c;
            
            if (curRow == 0 || curRow == numRows - 1) {
                goingDown = !goingDown;
            }
            
            curRow += goingDown ? 1 : -1;
        }

        string result;
        for (string row : rows) {
            result += row;
        }
        
        return result;
    }
};
```



### 23. 找出字符串中第一个匹配项的下标**

#### 23.1 题目

给你两个字符串 `haystack` 和 `needle` ，请你在 `haystack` 字符串中找出 `needle` 字符串的第一个匹配项的下标（下标从 0 开始）。如果 `needle` 不是 `haystack` 的一部分，则返回 `-1` 。

 

**示例 1：**

```
输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
```

**示例 2：**

```
输入：haystack = "leetcode", needle = "leeto"
输出：-1
解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。
```

 

**提示：**

- `1 <= haystack.length, needle.length <= 104`
- `haystack` 和 `needle` 仅由小写英文字符组成



#### 23.2 解法

时间复杂度 $O(n + m)$，空间复杂度为 $O(m)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int strStr(string haystack, string needle) {
    int j = 0, i = 1, n = needle.size();

    vector<int> next(n);
    next[0] = 0;

    while (i < n) {
      if (needle[i] == needle[j]) {
        next[i++] = ++j;
      } else if (j == 0) {
        next[i++] = j;
      } else {
        j = next[j - 1];
      }
    }

    j = 0;
    i = 0;
    while (i < haystack.size()) {
      if (haystack[i] == needle[j]) {
        i++;
        j++;
      } else if (j == 0) {
        i++;
      } else {
        j = next[j - 1];
      }

      if (j == n) return i - n;
    }

    return -1;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b;
  cin >> a >> b;

  Solution obj;
  cout << obj.strStr(a, b);

  return 0;
}
```



#### 23.3 解析

这就是最标准的最优解，也就是**KMP算法**。这个算法逻辑上很好理解，但是实现起来比较困难，特别是`next`数组的构造。

注意到暴力算法会在不匹配时让原串指针也回退，而回退的部分即为该算法的无用功，事实上既然原串已经扫描到此，就不必回退，保证原串只遍历一遍，就是KMP算法的核心特点。既然不希望原串指针回退，那么可能会在之前的部分匹配串中，出现这样的一种情况从而影响结果，即：**部分匹配串的后缀等于其本身的前缀**。也就是说，部分匹配串它的后缀必然和原串指针前的对应长度串是匹配的，而如果部分匹配串的前缀也等于这部分后缀，那么就意味着下一次的匹配依然开始，并进行到了上述三部分的长度值处。

进而，这个问题就变成了怎么求`needle`的前`i`长子串的最大匹配前后缀，也就是`next`数组的构造。这一块是整个算法最难理解的部分，其本质上是一个递推算法：令`next[i]`为`needle[0:i]`的最长匹配前后缀长度，`j`为当时最长前缀的末端`index`，此时比较`i+1`与`j+1`情况，如果仍然相等，则`next[i+1]`等于`j+1`；而当不等时，如果`j`等于0，那么`next[i+1]`就等于0，然后`i++`，如果不等于0，那么存在一种情况影响结果，即：`needle[i-j:i]`中可能存在后缀使得在`i+1`与`j+1`处能够匹配出新的最长前后缀，而`needle[i-j+1:i]`其实就与`needle[0:j-1]`相等，所以此时令`j = next[j - 1]`从而继续匹配。



### 24.  文本左右对齐*

#### 24.1 题目

给定一个单词数组 `words` 和一个长度 `maxWidth` ，重新排版单词，使其成为每行恰好有 `maxWidth` 个字符，且左右两端对齐的文本。

你应该使用 “**贪心算法**” 来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 `' '` 填充，使得每行恰好有 *maxWidth* 个字符。

要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入**额外的**空格。

**注意:**

- 单词是指由非空格字符组成的字符序列。
- 每个单词的长度大于 0，小于等于 *maxWidth*。
- 输入单词数组 `words` 至少包含一个单词。

 

**示例 1:**

```
输入: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
输出:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
```

**示例 2:**

```
输入:words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
输出:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
解释: 注意最后一行的格式应为 "shall be    " 而不是 "shall     be",
     因为最后一行应为左对齐，而不是左右两端对齐。       
     第二行同样为左对齐，这是因为这行只包含一个单词。
```

**示例 3:**

```
输入:words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]，maxWidth = 20
输出:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
```

 

**提示:**

- `1 <= words.length <= 300`
- `1 <= words[i].length <= 20`
- `words[i]` 由小写英文字母和符号组成
- `1 <= maxWidth <= 100`
- `words[i].length <= maxWidth`



#### 24.2 解法

时间复杂度 `O(N)`，空间复杂度 `O(N)`

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> lines;
    int lineLen = 0, lineSt = 0, n = words.size();

    for (int i = 0; i < n; i++) {
      if (words[i].size() + lineLen > maxWidth - max(0, i - lineSt)) {
        string newLine;

        for (int j = lineSt; j < i; j++) {
          newLine += words[j];
          int spaceNum = (maxWidth - lineLen) / max(1, (i - lineSt - 1));

          if (j < i - 1 || i - lineSt - 1 == 0) {
            for (int k = 0; k < spaceNum; k++) {
              newLine += " ";
            }
            if (j < lineSt + (maxWidth - lineLen) % max(1, (i - lineSt - 1))) {
              newLine += " ";
            }
          }
        }

        lines.push_back(newLine);
        lineSt = i--;
        lineLen = 0;
      } else {
        lineLen += words[i].size();

        if (i == n - 1) {
          string newLine;

          for (int j = lineSt; j < i + 1; j++) {
            newLine += words[j] + (j == i ? "" : " ");
            if (j == i) {
              int len = maxWidth - lineLen - i + lineSt;
              while (len-- > 0) newLine += " ";
            }
          }

          lines.push_back(newLine);
        }
      }
    }

    return lines;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, maxWidth;
  cin >> n >> maxWidth;
  cin.ignore();

  vector<string> words(n);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
  }

  Solution obj;
  vector<string> lines = obj.fullJustify(words, maxWidth);

  for (string x : lines) {
    cout << x << endl;
  }
  return 0;
}
```

> 稍微优化一下：
>
> ```cpp
> #include <iostream>
> #include <string>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<string> fullJustify(vector<string>& words, int maxWidth) {
>         vector<string> res;
>         int n = words.size();
>         int left = 0;
> 
>         while (left < n) {
>             int right = left;
>             int lineLen = 0;
> 
>             while (right < n && lineLen + words[right].size() + right - left <= maxWidth) {
>                 lineLen += words[right].size();
>                 right++;
>             }
> 
>             int numWords = right - left;
>             int numSpaces = maxWidth - lineLen;
>             string line;
> 
>             if (right == n || numWords == 1) {
>                 for (int i = left; i < right; i++) {
>                     line += words[i];
>                     if (i < right - 1) {
>                         line += " ";
>                     }
>                 }
>                 line += string(maxWidth - line.size(), ' ');
>             } else {
>                 int avgSpaces = numSpaces / (numWords - 1);
>                 int extraSpaces = numSpaces % (numWords - 1);
> 
>                 for (int i = left; i < right; i++) {
>                     line += words[i];
>                     if (i < right - 1) {
>                         int spacesToApply = avgSpaces + (i - left < extraSpaces ? 1 : 0);
>                         line += string(spacesToApply, ' ');
>                     }
>                 }
>             }
> 
>             res.push_back(line);
>             left = right;
>         }
> 
>         return res;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     int n, maxWidth;
>     if (cin >> n >> maxWidth) {
>         vector<string> words(n);
>         for (int i = 0; i < n; i++) {
>             cin >> words[i];
>         }
> 
>         Solution obj;
>         vector<string> lines = obj.fullJustify(words, maxWidth);
> 
>         for (const string& x : lines) {
>             cout << x << "\n";
>         }
>     }
>     return 0;
> }
> ```



#### 24.3 解析

这道题也算是达到最优解，但是它没什么技术含量，只是比较麻烦……



## 二、双指针



### 25. 验证回文串*

#### 25.1 题目

如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 **回文串** 。

字母和数字都属于字母数字字符。

给你一个字符串 `s`，如果它是 **回文串** ，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

```
输入: s = "A man, a plan, a canal: Panama"
输出：true
解释："amanaplanacanalpanama" 是回文串。
```

**示例 2：**

```
输入：s = "race a car"
输出：false
解释："raceacar" 不是回文串。
```

**示例 3：**

```
输入：s = " "
输出：true
解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
由于空字符串正着反着读都一样，所以是回文串。
```

 

**提示：**

- `1 <= s.length <= 2 * 105`
- `s` 仅由可打印的 ASCII 字符组成



#### 25.2 解法

时间复杂度 $O(n)$，空间复杂度 $O(1)$。

```cpp
#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    int left = 0, right = s.size();

    while (left < right) {
      if (!isalpha(s[left]) && !isdigit(s[left])) {
        left++;
      } else if (!isalpha(s[right]) && !isdigit(s[right])) {
        right--;
      } else {
        if (s[left] == s[right] || (isalpha(s[right]) && isalpha(s[left]) &&
                                    abs(s[left] - s[right]) == 32)) {
          left++;
          right--;
        } else {
          return false;
        }
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.isPalindrome(s);

  return 0;
}
```

> 首先`right`等于`s.size()`会越界，应该先减一，然后用`isalnum()` 可以直接判断字符是否为字母或数字，`tolower()` 可以统一把字符转为小写：
>
> ```cpp
> #include <cctype>
> #include <iostream>
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool isPalindrome(string s) {
>         int left = 0;
>         int right = s.size() - 1;
> 
>         while (left < right) {
>             if (!isalnum(s[left])) {
>                 left++;
>             } else if (!isalnum(s[right])) {
>                 right--;
>             } else {
>                 if (tolower(s[left]) != tolower(s[right])) {
>                     return false;
>                 }
>                 left++;
>                 right--;
>             }
>         }
> 
>         return true;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     string s;
>     getline(cin, s);
> 
>     Solution obj;
>     cout << (obj.isPalindrome(s) ? "true" : "false") << "\n";
> 
>     return 0;
> }
> ```



#### 25.6 解析

这就是最优解，此外，还有一种空间复杂度$O(n)$的预处理+翻转比对方法：

```cpp
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string cleanStr;

        for (char c : s) {
            if (isalnum(c)) {
                cleanStr += tolower(c);
            }
        }

        string revStr = cleanStr;
        reverse(revStr.begin(), revStr.end());

        return cleanStr == revStr;
    }
};
```



### 26. 判断子序列*/**

#### 26.1 题目

给定字符串 **s** 和 **t** ，判断 **s** 是否为 **t** 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，`"ace"`是`"abcde"`的一个子序列，而`"aec"`不是）。

**进阶：**

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

**致谢：**

特别感谢 [@pbrother ](https://leetcode.com/pbrother/)添加此问题并且创建所有测试用例。

 

**示例 1：**

```
输入：s = "abc", t = "ahbgdc"
输出：true
```

**示例 2：**

```
输入：s = "axc", t = "ahbgdc"
输出：false
```

 

**提示：**

- `0 <= s.length <= 100`
- `0 <= t.length <= 10^4`
- 两个字符串都只由小写字符组成。



#### 26.2 解法

时间复杂度 $O(n)$（$n$ 为 `t` 的长度），空间复杂度 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isSubsequence(string s, string t) {
    int j = 0, n = t.size(), m = s.size();

    if (n == 0 && m == 0) return true;

    for (int i = 0; i < n; i++) {
      if (t[i] == s[j]) {
        j++;
      }

      if (j >= m) {
        return true;
      }
    }

    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.isSubsequence(s, t);

  return 0;
}
```

> 对空串情况加了新判断，并换成`while`
>
> ```cpp
> #include <iostream>
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool isSubsequence(string s, string t) {
>         if (s.empty()) return true;
>         
>         int i = 0;
>         int j = 0;
>         
>         while (i < s.size() && j < t.size()) {
>             if (s[i] == t[j]) {
>                 i++;
>             }
>             j++;
>         }
>         
>         return i == s.size();
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     string s, t;
>     if (cin >> s >> t) {
>         Solution obj;
>         cout << (obj.isSubsequence(s, t) ? "true" : "false") << "\n";
>     }
> 
>     return 0;
> }
> ```



#### 26.7 解析

单次匹配时候确实算优解，但是对进阶来说还是差了些。而进阶的思路简单来说就是空间换时间，如果继续用双指针，每次比对都要把长为 $N$ 的主串 $T$ 遍历一遍，总时间复杂度会达到恐怖的 $O(k \times N)$；故而我们对主串T进行预处理，类似于构建一个确定性有限状态自动机（DFA）。

我们可以倒序遍历主串 $T$，构建一个二维的状态转移矩阵 `dp[i][26]`。 `dp[i][j]` 表示：从主串的下标 $i$ 开始往后看，字符 $j$（'a' 到 'z'）**第一次出现的位置**。预处理完成后，无论进来多少个短串 $S_i$，我们就像在查字典一样：可以直接 $O(1)$ 地跳跃到下一个匹配位置。对于每个短串，匹配时间从 $O(N)$ 降到了 $O(M)$（$M$ 为短串 $S_i$ 的长度）。总时间复杂度优化为 $O(N \times 26 + k \times M)$​。

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(26, 0));

        // 初始化边界，n代表越界（不存在）
        for (int c = 0; c < 26; c++) {
            dp[n][c] = n;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int c = 0; c < 26; c++) {
                // 匹配字母：如果t[i]是字母α，则对应为i；不是就是i+1时对应值
                if (t[i] == c + 'a') {
                    dp[i][c] = i;
                } else {
                    dp[i][c] = dp[i + 1][c];
                }
            }
        }

        int curr = 0;
        for (int i = 0; i < s.size(); i++) {
            if (curr == n) return false;
            
            curr = dp[curr][s[i] - 'a'];
            
            if (curr == n) return false;
            curr++;
        }

        return true;
    }
};
```



### 27. 两数之和II - 输入有序数组 *（@）

#### 27.1 题目

给你一个下标从 **1** 开始的整数数组 `numbers` ，该数组已按 **非递减顺序排列** ，请你从数组中找出满足相加之和等于目标数 `target` 的两个数。如果设这两个数分别是 `numbers[index1]` 和 `numbers[index2]` ，则 `1 <= index1 < index2 <= numbers.length` 。

以长度为 2 的整数数组 `[index1, index2]` 的形式返回这两个整数的下标 `index1` 和 `index2`。

你可以假设每个输入 **只对应唯一的答案** ，而且你 **不可以** 重复使用相同的元素。

你所设计的解决方案必须只使用常量级的额外空间。

 

**示例 1：**

```
输入：numbers = [2,7,11,15], target = 9
输出：[1,2]
解释：2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。
```

**示例 2：**

```
输入：numbers = [2,3,4], target = 6
输出：[1,3]
解释：2 与 4 之和等于目标数 6 。因此 index1 = 1, index2 = 3 。返回 [1, 3] 。
```

**示例 3：**

```
输入：numbers = [-1,0], target = -1
输出：[1,2]
解释：-1 与 0 之和等于目标数 -1 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。
```

 

**提示：**

- `2 <= numbers.length <= 3 * 104`
- `-1000 <= numbers[i] <= 1000`
- `numbers` 按 **非递减顺序** 排列
- `-1000 <= target <= 1000`
- **仅存在一个有效答案**



#### 27.2 解法

时间复杂度$O(n)$，空间复杂度为 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> a(2);
    int n = numbers.size(), i = 0;
    int j = n - 1;
    while (i < j) {
      if (numbers[i] + numbers[j] == target) {
        a[0] = i + 1;
        a[1] = j + 1;
        return a;
      } else if (numbers[i] + numbers[j] > target) {
        j--;
      } else {
        i++;
      }
    }

    return a;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, t;
  cin >> n >> t;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  vector<int> sum = obj.twoSum(nums, t);

  cout << sum[0] << " " << sum[1];
  return 0;
}
```

> 写法上可以优化，特别是返回数组时：
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<int> twoSum(vector<int>& numbers, int target) {
>         int left = 0;
>         int right = numbers.size() - 1;
> 
>         while (left < right) {
>             int current_sum = numbers[left] + numbers[right];
>             
>             if (current_sum == target) {
>                 // 不用额外初始化vector<int>
>                 return {left + 1, right + 1};
>             } else if (current_sum < target) {
>                 left++;
>             } else {
>                 right--;
>             }
>         }
> 
>         return {};
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     int n, t;
>     if (cin >> n >> t) {
>         vector<int> nums(n);
>         for (int i = 0; i < n; i++) {
>             cin >> nums[i];
>         }
> 
>         Solution obj;
>         vector<int> result = obj.twoSum(nums, t);
> 
>         if (!result.empty()) {
>             cout << result[0] << " " << result[1] << "\n";
>         }
>     }
> 
>     return 0;
> }
> ```
>
> 



#### 27.3 解析

同样是等效最优解。这是**对撞双指针**的核心题目，可以结合图片来看看，是选自LeetCode论坛上用户nettee的一篇[文章](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/solutions/87919/yi-zhang-tu-gao-su-ni-on-de-shuang-zhi-zhen-jie-fa)：

1. 正常搜索空间：

   <img src="./assets/image-20260315115048062.png" alt="image-20260315115048062" style="zoom:67%;" />

2. 从边角开始：

   <img src="./assets/image-20260315115120752.png" alt="image-20260315115120752" style="zoom:67%;" />

3. 如果小了，则下图部分不用搜索；反之旋转九十度部分不用搜索：

   <img src="./assets/image-20260315115212192.png" alt="image-20260315115212192" style="zoom: 67%;" />

4. 最后本质上就是在图中走了一条长度为n的线，所以是$O(n)$



### 28. 盛最多水的容器*

#### 28.1 题目

给定一个长度为 `n` 的整数数组 `height` 。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])` 。

找出其中的两条线，使得它们与 `x` 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

**说明：**你不能倾斜容器。

 

**示例 1：**

![img](./assets/question_11.jpg)

```
输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
```

**示例 2：**

```
输入：height = [1,1]
输出：1
```

 

**提示：**

- `n == height.length`
- `2 <= n <= 105`
- `0 <= height[i] <= 104`



#### 28.2 解法

时间复杂度$O(n)$，空间复杂度为 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxArea(vector<int>& height) {
    int i = 0, j = height.size() - 1, maxVol = 0;
    while (i < j) {
      int vol = (j - i) * min(height[i], height[j]);
      maxVol = max(vol, maxVol);

      if (height[i] < height[j]) {
        i++;
      } else {
        j--;
      }
    }

    return maxVol;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> heights(n);
  for (int i = 0; i < n; i++) {
    cin >> heights[i];
  }

  Solution obj;
  cout << obj.maxArea(heights);

  return 0;
}
```



#### 28.3 解析

这道题和上一道题其实差不多，关键一点是不要代入之前“接雨水”那道题的想法，因为这里不算柱子的空间，所以不用担心柱子影响体积，这是很关键的。明白这一点之后，同样取左右指针，那么考虑一个问题：移动哪一个指针，凭什么移动？注意到当`height[i] < height[j]`时，如果移动右边`j`，宽度一定减少，但是水位一定不变，这样容积一定减小，那么不能移动`j`，自然而然地就得移动`i`……



### 29. 三数之和*

#### 29.1 题目

给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请你返回所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。

 

**示例 1：**

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
```

**示例 2：**

```
输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
```

**示例 3：**

```
输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。
```

 

**提示：**

- `3 <= nums.length <= 3000`
- `-105 <= nums[i] <= 105`



#### 29.2 解法

时间复杂度：$O(n^2)$，空间复杂度：$O(\log n)$ 或 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    vector<vector<int>> result;

    int x = 0, n = nums.size();
    while (x < n - 2) {
      if (nums[x] + nums[n - 2] + nums[n - 1] < 0) {
        x++;
      } else if (nums[x] + nums[x + 1] + nums[x + 2] > 0) {
        break;
      } else if (1 <= x && nums[x] == nums[x - 1]) {
        x++;
        continue;
      }

      int y = x + 1, z = n - 1, sum = -nums[x];
      while (y < z) {
        if (z < n - 1 && y > x + 1 && nums[y] == nums[y - 1] &&
            nums[z] == nums[z + 1]) {
          z--;
          y++;
        } else if (nums[y] + nums[z] == sum) {
          result.push_back(vector<int>{nums[x], nums[y], nums[z]});
          z--;
          y++;
        } else if (nums[y] + nums[z] > sum) {
          z--;
        } else {
          y++;
        }
      }

      x++;
    }

    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  vector<vector<int>> res = obj.threeSum(nums);

  for (auto x : res) {
    cout << "[";
    for (int y : x) {
      cout << y << " ";
    }
    cout << "]\n";
  }

  return 0;
}
```

> 一些写法上的优化：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<vector<int>> threeSum(vector<int>& nums) {
>         vector<vector<int>> result;
>         int n = nums.size();
>         if (n < 3) return result;
> 
>         sort(nums.begin(), nums.end());
> 
>         // 如果x（或i）一定加，那么可以用for
>         for (int i = 0; i < n - 2; i++) {
>             // 新剪枝，本意就是旧剪枝的第二部分
>             if (nums[i] > 0) break;
>             
>             if (i > 0 && nums[i] == nums[i - 1]) continue;
> 
>             int left = i + 1;
>             int right = n - 1;
> 
>             while (left < right) {
>                 int sum = nums[i] + nums[left] + nums[right];
>                 
>                 if (sum == 0) {
>                     result.push_back({nums[i], nums[left], nums[right]});
>                     
>                     // 去重
>                     while (left < right && nums[left] == nums[left + 1]) left++;
>                     while (left < right && nums[right] == nums[right - 1]) right--;
>                     
>                     left++;
>                     right--;
>                 } else if (sum < 0) {
>                     left++;
>                 } else {
>                     right--;
>                 }
>             }
>         }
> 
>         return result;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     int n;
>     if (cin >> n) {
>         vector<int> nums(n);
>         for (int i = 0; i < n; i++) {
>             cin >> nums[i];
>         }
> 
>         Solution obj;
>         vector<vector<int>> res = obj.threeSum(nums);
> 
>         for (const auto& x : res) {
>             cout << "[";
>             for (size_t j = 0; j < x.size(); j++) {
>                 cout << x[j] << (j == x.size() - 1 ? "" : " ");
>             }
>             cout << "]\n";
>         }
>     }
>     return 0;
> }
> ```



#### 29.3 解析

这就是最优的解了，并没有量级上更快的办法。这道题相当于多了一个维度，其他部分和前面题目类似，稍微复杂的就是重复项的处理。



## 三、滑动窗口

### 30. 长度最小的子数组*

#### 30.1 题目

给定一个含有 `n` 个正整数的数组和一个正整数 `target` **。**

找出该数组中满足其总和大于等于 `target` 的长度最小的 **子数组** `[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度**。**如果不存在符合条件的子数组，返回 `0` 。

 

**示例 1：**

```
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
```

**示例 2：**

```
输入：target = 4, nums = [1,4,4]
输出：1
```

**示例 3：**

```
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
```

 

**提示：**

- `1 <= target <= 109`
- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 104`

 

**进阶：**

- 如果你已经实现 `O(n)` 时间复杂度的解法, 请尝试设计一个 `O(n log(n))` 时间复杂度的解法。



#### 30.2 解法

时间复杂度 $O(n)$，空间复杂度 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int i = 0, j = 1, n = nums.size(), sum = nums[0], minLen = 100001;
    if (n < 2) {
      return (sum >= target ? 1 : 0);
    }

    while (i < j) {
      if (sum >= target) {
        minLen = min(minLen, j - i);
        sum -= nums[i++];
      } else {
        if (j == n) break;
        sum += nums[j++];
      }
    }

    return (minLen == 100001 ? 0 : minLen);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, target;
  cin >> n >> target;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  cout << obj.minSubArrayLen(target, nums);

  return 0;
}
```

> 滑动窗口和双指针一样比较模板化，看看按模板写的（其实差不多）：
>
> ```cpp
> #include <algorithm>
> #include <climits>
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int minSubArrayLen(int target, vector<int>& nums) {
>         int minLen = INT_MAX; //INT_MAX更好
>         int left = 0;
>         int sum = 0;
>         int n = nums.size();
> 
>         for (int right = 0; right < n; right++) {
>             sum += nums[right];
> 
>             while (sum >= target) {
>                 minLen = min(minLen, right - left + 1);
>                 sum -= nums[left];
>                 left++;
>             }
>         }
> 
>         return minLen == INT_MAX ? 0 : minLen;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     int n, target;
>     if (cin >> n >> target) {
>         vector<int> nums(n);
>         for (int i = 0; i < n; i++) {
>             cin >> nums[i];
>         }
> 
>         Solution obj;
>         cout << obj.minSubArrayLen(target, nums) << "\n";
>     }
> 
>     return 0;
> }
> ```
>
> 



#### 30.3 解析

这就是等效最优解。注意到这道题是**大于等于**，不要误以为是等于即可。

进阶这部分是考虑到数字可能是负数，这样就没有$O(n)$了，不过这是另一个题目的解，这里先不说。



### 31. 无重复字符的最长子串*

#### 31.1 题目

给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长 子串** 的长度。

 

**示例 1:**

```
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
```

**示例 2:**

```
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
```

**示例 3:**

```
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```

 

**提示：**

- `0 <= s.length <= 5 * 104`
- `s` 由英文字母、数字、符号和空格组成



#### 31.2 解法

时间复杂度 $O(N)$，空间复杂度 $O(M)$（$M$ 为字符集大小）。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    int left = 1, n = s.size(), maxLen = 0;
    unordered_map<char, int> lastIndex;
    for (int right = 0; right < n; right++) {
      if (lastIndex[s[right]] >= left) {
        left = lastIndex[s[right]] + 1;
      }
      lastIndex[s[right]] = right + 1;
      maxLen = max(right - left + 2, maxLen);
    }

    return maxLen;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.lengthOfLongestSubstring(s);

  return 0;
}
```

> 由于只是ASCII码，以定长数组代替`unordered_map`速度会更快，顺便还解决了后者初始值是`0`的问题：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <string>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int lengthOfLongestSubstring(string s) {
>         vector<int> lastIndex(128, -1);
>         int maxLen = 0;
>         int left = 0;
>         
>         for (int right = 0; right < s.size(); right++) {
>             if (lastIndex[s[right]] >= left) {
>                 left = lastIndex[s[right]] + 1;
>             }
>             
>             lastIndex[s[right]] = right;
>             maxLen = max(maxLen, right - left + 1);
>         }
>         
>         return maxLen;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     string s;
>     if (getline(cin, s)) {
>         Solution obj;
>         cout << obj.lengthOfLongestSubstring(s) << "\n";
>     }
> 
>     return 0;
> }
> ```



#### 31.3 解析

这就是等效最优解，存下每个字符上一次出现的位置，如果在窗口中就直接缩减窗口左边界到该处（+1）。

此外，还可以用`bool`数组表征窗口状态：

```cpp
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 128位的布尔数组，表征窗口中是否有该字符
        vector<bool> window(128, false);
        int maxLen = 0;
        int left = 0;
        
        for (int right = 0; right < s.size(); right++) {
            // while循环代替跳转逻辑
            while (window[s[right]]) {
                window[s[left]] = false;
                left++;
            }
            
            window[s[right]] = true;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};
```



### 32. 串联所有单词的子串* （@）

#### 32.1 题目

给定一个字符串 `s` 和一个字符串数组 `words`**。** `words` 中所有字符串 **长度相同**。

 `s` 中的 **串联子串** 是指一个包含 `words` 中所有字符串以任意顺序排列连接起来的子串。

- 例如，如果 `words = ["ab","cd","ef"]`， 那么 `"abcdef"`， `"abefcd"`，`"cdabef"`， `"cdefab"`，`"efabcd"`， 和 `"efcdab"` 都是串联子串。 `"acdbef"` 不是串联子串，因为他不是任何 `words` 排列的连接。

返回所有串联子串在 `s` 中的开始索引。你可以以 **任意顺序** 返回答案。

 

**示例 1：**

```
输入：s = "barfoothefoobarman", words = ["foo","bar"]
输出：[0,9]
解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
输出顺序无关紧要。返回 [9,0] 也是可以的。
```

**示例 2：**

```
输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
输出：[]
解释：因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
所以我们返回一个空数组。
```

**示例 3：**

```
输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
输出：[6,9,12]
解释：因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。
```

 

**提示：**

- `1 <= s.length <= 104`
- `1 <= words.length <= 5000`
- `1 <= words[i].length <= 30`
- `words[i]` 和 `s` 由小写英文字母组成



#### 32.2 解法

时间复杂度$O(M)$（$M$ 为字符串 `s` 的长度），空间复杂度 $O(N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    unordered_map<string, int> wordsFeq;
    for (string x : words) wordsFeq[x]++;

    int wordLen = words[0].size(), n = words.size(), m = s.size();
    int subLen = wordLen * n;
    vector<int> res;

    for (int i = 0; i < wordLen; i++) {
      unordered_map<string, int> nowWordFeq;
      int left = i, nowMat = 0;
      for (int right = i; right <= m - wordLen; right += wordLen) {
        string sub = s.substr(right, wordLen);
        if (wordsFeq[sub] == 0) {
          left = right + wordLen;
          nowWordFeq.clear();
          nowMat = 0;
        } else {
          nowWordFeq[sub]++;
          nowMat++;
          while (wordsFeq[sub] < nowWordFeq[sub]) {
            string backSub = s.substr(left, wordLen);
            nowWordFeq[backSub]--;
            nowMat--;
            left += wordLen;
          }
          if (nowMat == n) {
            res.push_back(left);
            nowMat--;
            nowWordFeq[s.substr(left, wordLen)]--;
            left += wordLen;
          }
        }
      }
    }

    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<string> words(n);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
  }

  string s;
  cin >> s;

  Solution obj;
  vector<int> res = obj.findSubstring(s, words);
  for (int x : res) {
    cout << x << " ";
  }

  return 0;
}
```

> 此前我多次直接访问`unordered_map`中未有的元素，这时它会自动初始化为0，但是这样也会额外消耗内存：
>
> ```cpp
> #include <iostream>
> #include <string>
> #include <unordered_map>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<int> findSubstring(string s, vector<string>& words) {
>         vector<int> res;
>         if (words.empty() || s.empty()) return res;
> 
>         unordered_map<string, int> wordsFeq;
>         // const string& 节省空间
>         for (const string& word : words) {
>             wordsFeq[word]++;
>         }
> 
>         int wordLen = words[0].size();
>         int n = words.size();
>         int m = s.size();
> 
>         for (int i = 0; i < wordLen; i++) {
>             unordered_map<string, int> nowWordFeq;
>             int left = i;
>             int nowMat = 0;
> 
>             for (int right = i; right <= m - wordLen; right += wordLen) {
>                 string sub = s.substr(right, wordLen);
> 
>                 // 直接使用count就可以避免初始化它
>                 if (wordsFeq.count(sub) == 0) {
>                     nowWordFeq.clear();
>                     nowMat = 0;
>                     left = right + wordLen;
>                 } else {
>                     nowWordFeq[sub]++;
>                     nowMat++;
> 
>                     while (nowWordFeq[sub] > wordsFeq[sub]) {
>                         string backSub = s.substr(left, wordLen);
>                         nowWordFeq[backSub]--;
>                         nowMat--;
>                         left += wordLen;
>                     }
> 
>                     // 等于n后其实无需再移动，本次结束会自动right++移动，而必然导致超限，则使left++移动
>                     if (nowMat == n) {
>                         res.push_back(left);
>                     }
>                 }
>             }
>         }
> 
>         return res;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     int n;
>     if (cin >> n) {
>         vector<string> words(n);
>         for (int i = 0; i < n; i++) {
>             cin >> words[i];
>         }
> 
>         string s;
>         cin >> s;
> 
>         Solution obj;
>         vector<int> res = obj.findSubstring(s, words);
>         for (size_t i = 0; i < res.size(); i++) {
>             cout << res[i] << (i == res.size() - 1 ? "" : " ");
>         }
>         cout << "\n";
>     }
> 
>     return 0;
> }
> ```



#### 32.3 解析

这就是最优解。这个思路需要把所谓的`Words`看作一个个完整的单元，而做到这一点就需要以`[0:Words.size()]`为起点开始遍历数组，避免出现不从`N`的整数倍开始的子串。



### 33. 最小覆盖子串*

#### 33.1 题目

给定两个字符串 `s` 和 `t`，长度分别是 `m` 和 `n`，返回 s 中的 **最短窗口 子串**，使得该子串包含 `t` 中的每一个字符（**包括重复字符**）。如果没有这样的子串，返回空字符串 `""`。

测试用例保证答案唯一。

 

**示例 1：**

```
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
```

**示例 2：**

```
输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。
```

**示例 3:**

```
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。
```

 

**提示：**

- `m == s.length`
- `n == t.length`
- `1 <= m, n <= 105`
- `s` 和 `t` 由英文字母组成

 

**进阶：**你能设计一个在 `O(m + n)` 时间内解决此问题的算法吗？



#### 33.2 解法

时间复杂度$O(N)$，空间复杂度$O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {
    int m = s.size(), n = t.size();
    if (n > m) {
      return "";
    }

    vector<int> freq(128, -1), nowFreq(128, 0);
    for (const char& x : t) freq[x] += (freq[x] == -1 ? 2 : 1);

    int count = 0, left = 0, minLen = INT_MAX, minLeft = 0;
    for (int right = 0; right < m; right++) {
      if (freq[s[right]] != 0) {
        nowFreq[s[right]]++;
        if (nowFreq[s[right]] <= freq[s[right]]) count++;
      }
      if (count >= n) {
        while (nowFreq[s[left]] > freq[s[left]]) {
          if (freq[s[left]] != 0) {
            nowFreq[s[left]]--;
          }
          left++;
        }

        if (right - left + 1 < minLen) {
          minLen = right - left + 1;
          minLeft = left;
        }
      }
    }

    return (minLen == INT_MAX ? "" : s.substr(minLeft, minLen));
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.minWindow(s, t) << endl;

  return 0;
}
```



#### 33.3 解析

等效最优解，继承了上题的思路。此外，可以不用两个数组，上一题之所以用两个，是因为恢复起来很麻烦，这道题没有这个问题：

```cpp
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.size() < t.size()) {
            return "";
        }

        vector<int> hash(128, 0);
        for (char c : t) {
            hash[c]++;
        }

        int left = 0, count = t.size(), minLen = INT_MAX, minLeft = 0;

        for (int right = 0; right < s.size(); right++) {
            if (hash[s[right]] > 0) {
                count--;
            }
            hash[s[right]]--;

            // count==0表征当前窗口就是符合条件的窗口
            while (count == 0) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }

                // 如果当前窗口满足条件，则一定会左移一步，不论是否会破坏条件
                if (hash[s[left]] == 0) {
                    count++;
                }
                hash[s[left]]++;
                left++;
            }
        }

        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    if (cin >> s >> t) {
        Solution obj;
        cout << obj.minWindow(s, t) << "\n";
    }

    return 0;
}
```



## 四、矩阵

### 34. 有效的数独*/**

#### 34.1 题目

请你判断一个 `9 x 9` 的数独是否有效。只需要 **根据以下规则** ，验证已经填入的数字是否有效即可。

1. 数字 `1-9` 在每一行只能出现一次。
2. 数字 `1-9` 在每一列只能出现一次。
3. 数字 `1-9` 在每一个以粗实线分隔的 `3x3` 宫内只能出现一次。（请参考示例图）

 

**注意：**

- 一个有效的数独（部分已被填充）不一定是可解的。
- 只需要根据以上规则，验证已经填入的数字是否有效即可。
- 空白格用 `'.'` 表示。

 

**示例 1：**

![img](./assets/250px-sudoku-by-l2g-20050714svg.png)

```
输入：board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：true
```

**示例 2：**

```
输入：board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：false
解释：除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。 但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
```

 

**提示：**

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` 是一位数字（`1-9`）或者 `'.'`



#### 34.2 解法

**时间复杂度**：$O(1)$。**空间复杂度**：$O(1)$。

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> row(9, vector<bool>(9, false));
        vector<vector<bool>> col(9, vector<bool>(9, false));
        vector<vector<bool>> sqa(9, vector<bool>(9, false));

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '1';
                    int boxIndex = (i / 3) * 3 + j / 3;

                    if (row[i][num] || col[j][num] || sqa[boxIndex][num]) {
                        return false;
                    }

                    row[i][num] = true;
                    col[j][num] = true;
                    sqa[boxIndex][num] = true;
                }
            }
        }

        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<char>> board(9, vector<char>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }

    Solution obj;
    cout << (obj.isValidSudoku(board) ? "true" : "false") << "\n";

    return 0;
}
```



#### 34.3 解析

这道题一般都是等效最优解，但在其中亦有优劣，可以使用位运算代替bool数组：

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int> row(9, 0);
        vector<int> col(9, 0);
        vector<int> sqa(9, 0);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '1';
                    int mask = 1 << num; //把数字 1 向左移动 num 位，生成一个只有第 num 位是 1 的掩码
                    int boxIndex = (i / 3) * 3 + j / 3;

                    // 进行按位与操作，如果结果不为 0，说明这一位之前已经被标记过了（重复出现）
                    if ((row[i] & mask) || (col[j] & mask) || (sqa[boxIndex] & mask)) {
                        return false;
                    }

                    // 进行按位或操作，将当前数字的状态硬编码打入这个整数中
                    row[i] |= mask;
                    col[j] |= mask;
                    sqa[boxIndex] |= mask;
                }
            }
        }

        return true;
    }
};
```



### 35. 螺旋矩阵*

#### 35.1 题目

给你一个 `m` 行 `n` 列的矩阵 `matrix` ，请按照 **顺时针螺旋顺序** ，返回矩阵中的所有元素。

 

**示例 1：**

![img](./assets/spiral1.jpg)

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
```

**示例 2：**

![img](./assets/spiral.jpg)

```
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
```

 

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 10`
- `-100 <= matrix[i][j] <= 100`



#### 35.2 解法

**时间复杂度**：$O(M \times N)$，**空间复杂度**：$O(1)$。

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return {};

    int n = matrix.size();
    int m = matrix[0].size();
    int i = 0, j = 0, k = 0, count = 0;

    vector<vector<int>> move = {
        {0, 1, m - 1}, {1, 0, n - 1}, {0, -1, 0}, {-1, 0, 0}};
    vector<int> res;

    while (count < m * n - 1) {
      if (i * move[k][0] + j * move[k][1] <
          move[k][2] * move[k][0] + move[k][2] * move[k][1]) {
        res.push_back(matrix[i][j]);
        count++;
        i += move[k][0];
        j += move[k][1];
      } else {
        int change = (k + 3) % 4;
        move[change][2] -= move[change][0] + move[change][1];
        k = (k + 1) % 4;
      }
    }
    res.push_back(matrix[i][j]);

    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  if (cin >> n >> m) {
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> matrix[i][j];
      }
    }

    Solution obj;
    vector<int> res = obj.spiralOrder(matrix);

    for (size_t x = 0; x < res.size(); x++) {
      cout << res[x] << (x == res.size() - 1 ? "" : " ");
    }
    cout << "\n";
  }

  return 0;
}
```



#### 35.3 解析

算是等效最优解，但是逻辑稍微有点绕。`move`就是定义了四个方向的移动向量和边界，然后用一个投影算式统一表示了边界条件，最后更新边界注意是更新` (k + 3) % 4`。

此外，一般的做法更为清晰：

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};

        vector<int> res;
        int top = 0;
        int bottom = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;

        while (true) {
            for (int i = left; i <= right; i++) res.push_back(matrix[top][i]);
            if (++top > bottom) break;

            for (int i = top; i <= bottom; i++) res.push_back(matrix[i][right]);
            if (--right < left) break;

            for (int i = right; i >= left; i--) res.push_back(matrix[bottom][i]);
            if (--bottom < top) break;

            for (int i = bottom; i >= top; i--) res.push_back(matrix[i][left]);
            if (++left > right) break;
        }

        return res;
    }
};
```



### 36. 旋转图像*/**

#### 36.1 题目

给定一个 *n* × *n* 的二维矩阵 `matrix` 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在**[ 原地](https://baike.baidu.com/item/原地算法)** 旋转图像，这意味着你需要直接修改输入的二维矩阵。**请不要** 使用另一个矩阵来旋转图像。

 

**示例 1：**

![img](./assets/mat1.jpg)

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
```

**示例 2：**

![img](./assets/mat2.jpg)

```
输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

 

**提示：**

- `n == matrix.length == matrix[i].length`
- `1 <= n <= 20`
- `-1000 <= matrix[i][j] <= 1000`



#### 36.2 解法

**时间复杂度**：$O(N^2)$，**空间复杂度**：$O(1)$。

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = n - 1; i >= n / 2; i--) {
      int layer = n - 1 - i;
      for (int j = 0; j < i - layer; j++) {
        int temp = matrix[layer][layer + j];
        matrix[layer][layer + j] = matrix[i - j][layer];
        matrix[i - j][layer] = matrix[i][i - j];
        matrix[i][i - j] = matrix[layer + j][i];
        matrix[layer + j][i] = temp;
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  if (cin >> n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> matrix[i][j];
      }
    }

    Solution obj;
    obj.rotate(matrix);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << matrix[i][j] << (j == n - 1 ? "" : " ");
      }
      cout << "\n";
    }
  }

  return 0;
}
```



#### 36.3 解析

我这个解当然也算最优解，但是有一个更好的办法：将一个二维矩阵顺时针旋转 90 度，在数学上等价于以下两步：

1. **主对角线翻转（转置）**：将矩阵的行和列互换（`matrix[i][j]` 与 `matrix[j][i]` 互换）。
2. **左右镜像翻转**：将转置后的矩阵，每一行进行水平翻转（逆序）。

那么：

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
```



### 37. 矩阵置零**

#### 37.1 题目

给定一个 `*m* x *n*` 的矩阵，如果一个元素为 **0** ，则将其所在行和列的所有元素都设为 **0** 。请使用 **[原地](http://baike.baidu.com/item/原地算法)** 算法**。**

 

**示例 1：**

![img](./assets/mat1-1773981443932-1.jpg)

```
输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]
```

**示例 2：**

![img](./assets/mat2-1773981443932-3.jpg)

```
输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```

 

**提示：**

- `m == matrix.length`
- `n == matrix[0].length`
- `1 <= m, n <= 200`
- `-231 <= matrix[i][j] <= 231 - 1`

 

**进阶：**

- 一个直观的解决方案是使用  `O(*m**n*)` 的额外空间，但这并不是一个好的解决方案。
- 一个简单的改进方案是使用 `O(*m* + *n*)` 的额外空间，但这仍然不是最好的解决方案。
- 你能想出一个仅使用常量空间的解决方案吗？



#### 37.2 解法

**时间复杂度**：$O(M \times N)$，**空间复杂度**：$O(M+N)$ 。

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> rowZero(n, 1);
        vector<int> colZero(m, 1);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    rowZero[i] = 0;
                    colZero[j] = 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (rowZero[i] == 0 || colZero[j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (cin >> n >> m) {
        vector<vector<int>> matrix(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> matrix[i][j];
            }
        }

        Solution obj;
        obj.setZeroes(matrix);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << matrix[i][j] << (j == m - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }

    return 0;
}
```



#### 37.3 解析

这并不是最优解，最优解的空间复杂度能到达$O(1)$。但是所谓的最优解并没有思维上的跃进，它是征用了原矩阵第一行、第一列作为原本`M + N`的空间（因为如果对应行列有零，那么第一行、列的对应位置也一定会是零，并不需要备份原矩阵的第一行、列），算是一个比较巧妙的办法：

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        // 两个布尔变量标记第一行、列是否需要全部置零。
        bool firstRowZero = false;
        bool firstColZero = false;

        // 扫描第一行、列
        for (int i = 0; i < n; i++) {
            if (matrix[i][0] == 0) firstColZero = true;
        }
        for (int j = 0; j < m; j++) {
            if (matrix[0][j] == 0) firstRowZero = true;
        }

        // 存储行列状态
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // 处理0
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 处理第一行、列
        if (firstColZero) {
            for (int i = 0; i < n; i++) {
                matrix[i][0] = 0;
            }
        }
        if (firstRowZero) {
            for (int j = 0; j < m; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};
```



### 38. 生命游戏**

#### 38.1 题目

根据 [百度百科](https://baike.baidu.com/item/生命游戏/2926434?fr=aladdin) ， **生命游戏** ，简称为 **生命** ，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。

给定一个包含 `m × n` 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态： `1` 即为 **活细胞** （live），或 `0` 即为 **死细胞** （dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

1. 如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
2. 如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
3. 如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
4. 如果死细胞周围正好有三个活细胞，则该位置死细胞复活；

下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是 **同时** 发生的。给你 `m x n` 网格面板 `board` 的当前状态，返回下一个状态。

给定当前 `board` 的状态，**更新** `board` 到下一个状态。

**注意** 你不需要返回任何东西。

 

**示例 1：**

![img](./assets/grid1.jpg)

```
输入：board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
输出：[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
```

**示例 2：**

![img](./assets/grid2.jpg)

```
输入：board = [[1,1],[1,0]]
输出：[[1,1],[1,1]]
```

 

**提示：**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 25`
- `board[i][j]` 为 `0` 或 `1`

 

**进阶：**

- 你可以使用原地算法解决本题吗？请注意，面板上所有格子需要同时被更新：你不能先更新某些格子，然后使用它们的更新后的值再更新其他格子。
- 本题中，我们使用二维数组来表示面板。原则上，面板是无限的，但当活细胞侵占了面板边界时会造成问题。你将如何解决这些问题？



#### 38.2 解法

时间复杂度为 $O(M \times N)$，空间复杂度为 $O(M \times N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  void gameOfLife(vector<vector<int>>& board) {
    int m = board[0].size(), n = board.size();
    vector<vector<int>> nextState(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 1) {
          nextState[i][j] += board[i][j];
          if (i > 0) {
            nextState[i - 1][j]++;
          }
          if (j > 0) {
            nextState[i][j - 1]++;
          }
          if (i < n - 1) {
            nextState[i + 1][j]++;
          }
          if (j < m - 1) {
            nextState[i][j + 1]++;
          }
          if (i > 0 && j > 0) {
            nextState[i - 1][j - 1]++;
          }
          if (i > 0 && j < m - 1) {
            nextState[i - 1][j + 1]++;
          }
          if (i < n - 1 && j > 0) {
            nextState[i + 1][j - 1]++;
          }
          if (i < n - 1 && j < m - 1) {
            nextState[i + 1][j + 1]++;
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 0) {
          if (nextState[i][j] == 3) board[i][j] = 1;
        } else {
          if (nextState[i][j] > 4 || nextState[i][j] < 3) board[i][j] = 0;
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m, n;
  cin >> m >> n;

  vector<vector<int>> matrix(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> matrix[i][j];
    }
  }

  Solution obj;
  obj.gameOfLife(matrix);

  for (vector<int> r : matrix) {
    for (int c : r) {
      cout << c << " ";
    }
    cout << endl;
  }

  return 0;
}
```

> 很多冗余的`if`分支，这里可以使用**方向数组**：
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     void gameOfLife(vector<vector<int>>& board) {
>         int n = board.size();
>         int m = board[0].size();
>         vector<vector<int>> nextState(n, vector<int>(m, 0));
> 
>         // 定义方向数组，即(i + dx[k], j + dy[k])
>         int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
>         int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
> 
>         for (int i = 0; i < n; i++) {
>             for (int j = 0; j < m; j++) {
>                 if (board[i][j] == 1) {
>                     nextState[i][j] += 1;
>                     
>                     for (int k = 0; k < 8; k++) {
>                         int nx = i + dx[k];
>                         int ny = j + dy[k];
>                         
>                         // 条件判断压缩成一句
>                         if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
>                             nextState[nx][ny] += 1;
>                         }
>                     }
>                 }
>             }
>         }
> 
>         for (int i = 0; i < n; i++) {
>             for (int j = 0; j < m; j++) {
>                 if (board[i][j] == 0) {
>                     if (nextState[i][j] == 3) board[i][j] = 1;
>                 } else {
>                     if (nextState[i][j] > 4 || nextState[i][j] < 3) board[i][j] = 0;
>                 }
>             }
>         }
>     }
> };
> ```
>
> 



#### 38.3 解析

这也不算是等效最优解。

最优解和上一题一样，都是借用原矩阵空间，这里由于数据只占用0和1两个数字，也就是1位，而`int`还剩31位没有用到，这时候就可以借用此后的比特位来存储`nextState`。

下面是八个方向扫描的做法，当然用这种思路也可以实现我的办法（也就是活细胞贡献法）：

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        if (board.empty() || board[0].empty()) return;
        
        int m = board.size();
        int n = board[0].size();
        
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int liveNeighbors = 0;
                
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n) {
                        liveNeighbors += (board[x][y] & 1);
                    }
                }

                // 满足继续存活或者复活条件，即写入第二位 1
                if ((board[i][j] & 1) == 1) {
                    if (liveNeighbors == 2 || liveNeighbors == 3) {
                        board[i][j] |= 2;
                    }
                } else {
                    if (liveNeighbors == 3) {
                        board[i][j] |= 2;
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] >>= 1;
            }
        }
    }
};
```



## 五、哈希

### 39. 赎金信*

#### 39.1 题目

给你两个字符串：`ransomNote` 和 `magazine` ，判断 `ransomNote` 能不能由 `magazine` 里面的字符构成。

如果可以，返回 `true` ；否则返回 `false` 。

`magazine` 中的每个字符只能在 `ransomNote` 中使用一次。

 

**示例 1：**

```
输入：ransomNote = "a", magazine = "b"
输出：false
```

**示例 2：**

```
输入：ransomNote = "aa", magazine = "ab"
输出：false
```

**示例 3：**

```
输入：ransomNote = "aa", magazine = "aab"
输出：true
```

 

**提示：**

- `1 <= ransomNote.length, magazine.length <= 105`
- `ransomNote` 和 `magazine` 由小写英文字母组成



#### 39.2 解法

时间复杂度 $O(m + n)$，空间复杂度$O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canConstruct(string ransomNote, string magazine) {
    vector<int> freq(128);
    int n = ransomNote.size();

    for (char x : magazine) freq[x]++;

    for (int i = 0; i < n; i++) {
      if (--freq[ransomNote[i]] < 0) {
        return false;
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.canConstruct(s, t);

  return 0;
}
```

> 可以多加一个判断（拦截）条件：
>
> ```cpp
> class Solution {
> public:
>     bool canConstruct(string ransomNote, string magazine) {
>         if (ransomNote.size() > magazine.size()) {
>             return false;
>         }
> 
>         vector<int> freq(128, 0);
> 
>         for (char x : magazine) {
>             freq[x]++;
>         }
> 
>         for (char x : ransomNote) {
>             if (--freq[x] < 0) {
>                 return false;
>             }
>         }
> 
>         return true;
>     }
> };
> ```



#### 39.3 解析

典型的简单题，没什么太多注意的，这题`hash`数量很少，可以不用`unordered_map`。



### 40. 同构字符串*

#### 40.1 题目

给定两个字符串 `s` 和 `t` ，判断它们是否是同构的。

如果 `s` 中的字符可以按某种映射关系替换得到 `t` ，那么这两个字符串是同构的。

每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。

 

**示例 1：**

**输入：**s = "egg", t = "add"

**输出：**true

**解释：**

字符串 `s` 和 `t` 可以通过以下方式变得相同：

- 将 `'e'` 映射为 `'a'`。
- 将 `'g'` 映射为 `'d'`。

**示例 2：**

**输入：**s = "f11", t = "b23"

**输出：**false

**解释：**

字符串 `s` 和 `t` 无法变得相同，因为 `'1'` 需要同时映射到 `'2'` 和 `'3'`。

**示例 3：**

**输入：**s = "paper", t = "title"

**输出：**true

 

**提示：**



- `1 <= s.length <= 5 * 104`
- `t.length == s.length`
- `s` 和 `t` 由任意有效的 ASCII 字符组成



#### 40.2 解法

时间复杂度 $O(N)$，空间复杂度 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    int n = s.size();
    if (n != t.size()) return false;

    vector<int> map(128, -1), reverseMap(128, 0);

    for (int i = 0; i < n; i++) {
      if (map[s[i]] == -1) {
        if (reverseMap[t[i]] == 0) {
          map[s[i]] = t[i];
          reverseMap[t[i]]++;
        } else {
          return false;
        }
      } else {
        if (map[s[i]] != t[i]) return false;
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.isIsomorphic(s, t);

  return 0;
}
```

> 这其实是一个双射模型，可以写得更加对称：
>
> ```cpp
> #include <iostream>
> #include <string>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool isIsomorphic(string s, string t) {
>         if (s.size() != t.size()) return false;
> 
>         vector<int> s2t(128, -1);
>         vector<int> t2s(128, -1);
> 
>         for (int i = 0; i < s.size(); i++) {
>             char cs = s[i];
>             char ct = t[i];
> 
>             if (s2t[cs] == -1 && t2s[ct] == -1) {
>                 s2t[cs] = ct;
>                 t2s[ct] = cs;
>             } else if (s2t[cs] != ct || t2s[ct] != cs) {
>                 return false;
>             }
>         }
> 
>         return true;
>     }
> };
> ```



#### 40.3 解析

同样地是典型的简单题，属于双Hash的开篇。不过除了双射法，还有一种比较巧妙的办法：注意到如果两个字符串是同构的，那么它们对应位置的字符，其“上一次出现的位置”必须是一致的：

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) return false;

        vector<int> lastSeenS(128, 0);
        vector<int> lastSeenT(128, 0);

        for (int i = 0; i < s.size(); i++) {
            if (lastSeenS[s[i]] != lastSeenT[t[i]]) {
                return false;
            }
            
            lastSeenS[s[i]] = i + 1;
            lastSeenT[t[i]] = i + 1;
        }

        return true;
    }
};
```



### 41. 单词规律*

#### 41.1 题目

给定一种规律 `pattern` 和一个字符串 `s` ，判断 `s` 是否遵循相同的规律。

这里的 **遵循** 指完全匹配，例如， `pattern` 里的每个字母和字符串 `s` 中的每个非空单词之间存在着双向连接的对应规律。具体来说：

- `pattern` 中的每个字母都 **恰好** 映射到 `s` 中的一个唯一单词。
- `s` 中的每个唯一单词都 **恰好** 映射到 `pattern` 中的一个字母。
- 没有两个字母映射到同一个单词，也没有两个单词映射到同一个字母。

 

**示例1:**

```
输入: pattern = "abba", s = "dog cat cat dog"
输出: true
```

**示例 2:**

```
输入:pattern = "abba", s = "dog cat cat fish"
输出: false
```

**示例 3:**

```
输入: pattern = "aaaa", s = "dog cat cat dog"
输出: false
```

 

**提示:**

- `1 <= pattern.length <= 300`
- `pattern` 只包含小写英文字母
- `1 <= s.length <= 3000`
- `s` 只包含小写英文字母和 `' '`
- `s` **不包含** 任何前导或尾随对空格
- `s` 中每个单词都被 **单个空格** 分隔



#### 41.2 解法

**时间复杂度**：$O(N + M)$，**空间复杂度**：$O(M)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool wordPattern(string pattern, string s) {
    istringstream iss(s);
    string word;
    unordered_map<string, int> s2p;
    vector<string> p2s(128, "");

    for (char x : pattern) {
      iss >> word;
      if (word == "") return false;
      if (p2s[x] == "" && s2p.count(word) == 0) {
        p2s[x] = word;
        s2p[word] = x;
      } else {
        if (p2s[x] != word || s2p[word] != x) return false;
      }
    }
    if (iss >> word) return false;

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string pattern, s;
  cin >> pattern;
  cin.ignore();
  getline(cin, s);

  Solution obj;
  cout << obj.wordPattern(pattern, s);

  return 0;
}
```

> 流处理可以优化：
>
> ```cpp
> #include <iostream>
> #include <sstream>
> #include <string>
> #include <unordered_map>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool wordPattern(string pattern, string s) {
>         istringstream iss(s);
>         string word;
>         unordered_map<string, char> s2p;
>         vector<string> p2s(128, "");
> 
>         for (char x : pattern) {
>             // 直接判断是否读取出
>             if (!(iss >> word)) {
>                 return false;
>             }
> 
>             if (p2s[x] == "" && s2p.count(word) == 0) {
>                 p2s[x] = word;
>                 s2p[word] = x;
>             } else if (p2s[x] != word) {//双射判断单边即可
>                 return false;
>             }
>         }
> 
>         if (iss >> word) {
>             return false;
>         }
> 
>         return true;
>     }
> };
> ```



#### 41.3 解析

算是等效最优解，但是一般认为先把流`iss`处理成一个字符串向量会更好一些，当然这也会消耗更多的空间。



### 42. 有效的字母异位词*

#### 42.1 题目

给定两个字符串 `s` 和 `t` ，编写一个函数来判断 `t` 是否是 `s` 的 字母异位词（字母异位词是通过重新排列不同单词或短语的字母而形成的单词或短语，并使用所有原字母一次。）。

 

**示例 1:**

```
输入: s = "anagram", t = "nagaram"
输出: true
```

**示例 2:**

```
输入: s = "rat", t = "car"
输出: false
```

 

**提示:**

- `1 <= s.length, t.length <= 5 * 104`
- `s` 和 `t` 仅包含小写字母

 

**进阶:** 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？



#### 42.2 解法

时间复杂度 $O(N)$，空间复杂度 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isAnagram(string s, string t) {
    int count = t.size();
    if (count != s.size()) return false;

    vector<int> freq(128);
    for (char x : t) freq[x]++;

    for (char x : s) {
      if (--freq[x] < 0) {
        return false;
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.isAnagram(s, t);

  return 0;
}
```

> 很多时候只需要管字母，也就是长为26的数组：
>
> ```cpp
> #include <iostream>
> #include <string>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool isAnagram(string s, string t) {
>         if (s.size() != t.size()) {
>             return false;
>         }
> 
>         vector<int> freq(26, 0);
> 
>         for (char c : s) {
>             freq[c - 'a']++;
>         }
> 
>         for (char c : t) {
>             if (--freq[c - 'a'] < 0) {
>                 return false;
>             }
>         }
> 
>         return true;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     string s, t;
>     if (cin >> s >> t) {
>         Solution obj;
>         cout << (obj.isAnagram(s, t) ? "true" : "false") << "\n";
>     }
> 
>     return 0;
> }
> ```
>
> 



#### 42.3 解析

这当然是两两比较的最优解，但是如果字符串多了起来，比如到达$10^4$ 量级……可以考虑排序法：

```cpp
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        
        return s == t;
    }
};
```

当然这的时间复杂度退化为 $O(N \log N)$，空间复杂度通常为 $O(1)$ 或 $O(\log N)$（取决于 C++ 底层排序的栈空间）。



### 43. 字母异位词分组**

#### 43.1 题目

给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

 

**示例 1:**

**输入:** strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

**输出:** [["bat"],["nat","tan"],["ate","eat","tea"]]

**解释：**

- 在 strs 中没有字符串可以通过重新排列来形成 `"bat"`。
- 字符串 `"nat"` 和 `"tan"` 是字母异位词，因为它们可以重新排列以形成彼此。
- 字符串 `"ate"` ，`"eat"` 和 `"tea"` 是字母异位词，因为它们可以重新排列以形成彼此。

**示例 2:**

**输入:** strs = [""]

**输出:** [[""]]

**示例 3:**

**输入:** strs = ["a"]

**输出:** [["a"]]

 

**提示：**

- `1 <= strs.length <= 104`
- `0 <= strs[i].length <= 100`
- `strs[i]` 仅包含小写字母



#### 43.2 解法

**时间复杂度**：$O(N \times K \log K)$，**空间复杂度**：$O(N \times K)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    int n = strs.size();
    vector<vector<string>> res;
    unordered_map<string, int> index;

    for (int i = 0; i < n; i++) {
      string word = strs[i];
      sort(strs[i].begin(), strs[i].end());

      if (index.count(strs[i]) != 0) {
        res[index[strs[i]]].push_back(word);
      } else {
        res.push_back({word});
        index[strs[i]] = res.size() - 1;
      }
    }

    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  cin.ignore();

  vector<string> strs(n);
  for (int i = 0; i < n; i++) {
    cin >> strs[i];
  }

  Solution obj;
  vector<vector<string>> res = obj.groupAnagrams(strs);

  for (vector<string> group : res) {
    for (string x : group) {
      cout << x << " ";
    }
    cout << endl;
  }

  return 0;
}
```

> 主要有一个问题，就是传入的`strs`是一个引用，如果`sort`就会把原数组给修改了，这样不妥：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <string>
> #include <unordered_map>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<vector<string>> groupAnagrams(vector<string>& strs) {
>         unordered_map<string, vector<string>> groups;
> 
>         for (const string& s : strs) {
>             // 用副本排序，而不是用副本作为索引
>             string key = s;
>             sort(key.begin(), key.end());
>             groups[key].push_back(s);
>         }
> 
>         vector<vector<string>> res;
>         res.reserve(groups.size());
>         
>         // 映射表不存索引，而是字符串向量本身，之后用move高效地（O(1)）转移
>         for (auto& pair : groups) {
>             res.push_back(move(pair.second));
>         }
> 
>         return res;
>     }
> };
> ```



#### 43.3 解析

这并不算最优解，还有一种利用`42题`的频次统计，再结合`hash表`的高效算法：

异位词的本质是“各个字符出现的频次相同”，而题目限定了只有 26 个小写字母。这样我们可以统计每个词的字母频率，然后格式化成一个字符串，类似`"2#0#1#0...0"`，并以之作为映射表的索引：

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {
            // 直接定义字符串，利用其数组（向量）特性
            string key(26, 0); 
            for (char c : s) {
                key[c - 'a']++; 
            }
            groups[key].push_back(s);
        }

        vector<vector<string>> res;
        res.reserve(groups.size());
        for (auto& pair : groups) {
            res.push_back(move(pair.second));
        }

        return res;
    }
};
```

这样的算法将单个字符串的处理时间从 $O(K \log K)$ 降到了 $O(K)$，整体时间复杂度降低为 $O(N \times K)$；空间复杂度等价。



### 44. 两数之和*

#### 44.1 题目

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** *`target`* 的那 **两个** 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。

 

**示例 1：**

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

**示例 2：**

```
输入：nums = [3,2,4], target = 6
输出：[1,2]
```

**示例 3：**

```
输入：nums = [3,3], target = 6
输出：[0,1]
```

 

**提示：**

- `2 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`
- **只会存在一个有效答案**

 

**进阶：**你可以想出一个时间复杂度小于 `O(n2)` 的算法吗？



#### 44.2 解法

**时间复杂度**：$O(N)$，**空间复杂度**：$O(N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> index;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int sub = target - nums[i];
      if (index.count(sub) != 0) {
        return {index[sub], i};
      } else {
        index[nums[i]] = i;
      }
    }

    return {};
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, target;
  cin >> n >> target;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  vector<int> res = obj.twoSum(nums, target);
  // 这个输出可能有问题（越界），加一个判断即可
  cout << res[0] << " " << res[1];

  return 0;
}
```



#### 44.3 解析

由于题目要求返回原始下标，所以不太可能不用额外的空间，如果要比$O(N^2)$更快，一个是我这个办法；另一个就是排序+双指针（两数之和II），后者限于排序速度，所以还是我这种为最优。当然如果只是返回数字，综合来看后者也是很不错的，空间复杂度仅$O(1)$。





### 45. 快乐数**

#### 45.1 题目

编写一个算法来判断一个数 `n` 是不是快乐数。

**「快乐数」** 定义为：

- 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
- 然后重复这个过程直到这个数变为 1，也可能是 **无限循环** 但始终变不到 1。
- 如果这个过程 **结果为** 1，那么这个数就是快乐数。

如果 `n` 是 *快乐数* 就返回 `true` ；不是，则返回 `false` 。

 

**示例 1：**

```
输入：n = 19
输出：true
解释：
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

**示例 2：**

```
输入：n = 2
输出：false
```

 

**提示：**

- `1 <= n <= 231 - 1`



#### 45.2 解法

**时间复杂度**：$O(\log n)$，**空间复杂度**：$O(\log n)$。

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isHappy(int n) {
    unordered_map<int, int> circ;
    while (circ.count(n) == 0) {
      circ[n] = 1;
      int m = n, sum = 0;
      while (m != 0) {
        sum += int(pow(m % 10, 2));
        m /= 10;
      }
      if (sum == 1) return true;
      n = sum;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  Solution obj;
  cout << obj.isHappy(n);

  return 0;
}
```

> 一方面`pow`比较慢；另一方面，如果只用到`hash`的`key`，可以用`set`:
>
> ```cpp
> #include <iostream>
> #include <unordered_set>
> 
> using namespace std;
> 
> class Solution {
> private:
>     int getNext(int n) {
>         int totalSum = 0;
>         while (n > 0) {
>             int d = n % 10;
>             totalSum += d * d;
>             n /= 10;
>         }
>         return totalSum;
>     }
> 
> public:
>     bool isHappy(int n) {
>         unordered_set<int> seen;
>         
>         // 集合只判断有没有
>         while (n != 1 && !seen.count(n)) {
>             seen.insert(n); // 插入集合
>             n = getNext(n);
>         }
>         
>         return n == 1;
>     }
> };
> ```



#### 45.3 解析

这当然也不算最优解，此外还有空间 $O(1)$ 的解法。既然是判断是否循环，那么其实可以使用快慢指针（即Floyd 判圈算法）：让一个指针跑得更快，当他们相遇，则一定有环；而若有环，则一定相遇：

```cpp
#include <iostream>

using namespace std;

class Solution {
private:
    // 计算平方和独立函数
    int getNext(int n) {
        int totalSum = 0;
        while (n > 0) {
            int d = n % 10;
            totalSum += d * d;
            n /= 10;
        }
        return totalSum;
    }

public:
    bool isHappy(int n) {
        int slow = n;
        int fast = getNext(n);
        
        while (fast != 1 && slow != fast) {
            slow = getNext(slow); // 慢指针单步长
            fast = getNext(getNext(fast)); // 快指针双步长
        }
        
        return fast == 1;
    }
};
```





### 46. 存在重复元素II*/**

#### 46.1 题目

给你一个整数数组 `nums` 和一个整数 `k` ，判断数组中是否存在两个 **不同的索引** `i` 和 `j` ，满足 `nums[i] == nums[j]` 且 `abs(i - j) <= k` 。如果存在，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

```
输入：nums = [1,2,3,1], k = 3
输出：true
```

**示例 2：**

```
输入：nums = [1,0,1,1], k = 1
输出：true
```

**示例 3：**

```
输入：nums = [1,2,3,1,2,3], k = 2
输出：false
```

 

 

**提示：**

- `1 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`
- `0 <= k <= 105`



#### 46.2 解法

时间复杂度 $O(N)$，空间复杂度 $O(N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> index;
    for (int i = 0; i < n; i++) {
      if (index.count(nums[i]) != 0 && i - index[nums[i]] <= k) {
        return true;
      }
      index[nums[i]] = i;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  cout << obj.containsNearbyDuplicate(nums, k);

  return 0;
}
```

> 还可以用`find`获得迭代器，这样比我的两次哈希寻址好一点。
>
> ```cpp
> #include <iostream>
> #include <unordered_map>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool containsNearbyDuplicate(vector<int>& nums, int k) {
>         unordered_map<int, int> index;
>         
>         for (int i = 0; i < nums.size(); i++) {
>             auto it = index.find(nums[i]);
>             
>             // 前者表示找到了，后者用->取值
>             if (it != index.end() && i - it->second <= k) {
>                 return true;
>             }
>             index[nums[i]] = i;
>         }
>         
>         return false;
>     }
> };
> ```



#### 46.3 解析

算半个等效最优解吧，事实上还有更好的办法，能够把空间复杂度降低到$O(\min(N, k))$。其实不难看出不需要遍历整个数组，而只需要维护一个长度为`k`的滑动窗口即可：前者意味着$O(N)$的空间复杂度，而后者则是$O(\min(N, k))$。

```cpp
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> window;
        
        for (int i = 0; i < nums.size(); i++) {
            // 当窗口大于k，移除尾部
            if (i > k) {
                window.erase(nums[i - k - 1]);
            }
            
            // 如果无法插入集合，即在k内有重复
            if (!window.insert(nums[i]).second) {
                return true;
            }
        }
        
        return false;
    }
};
```



### 47. 最长连续序列***

#### 47.1 题目

给定一个未排序的整数数组 `nums` ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 `O(n)` 的算法解决此问题。

 

**示例 1：**

```
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
```

**示例 2：**

```
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9
```

**示例 3：**

```
输入：nums = [1,0,1,2]
输出：3
```

 

**提示：**

- `0 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`



#### 47.2 解法

**时间复杂度**： **$O(N)$**，**空间复杂度**：**$O(N)$**。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    int n = nums.size(), maxLen = 0;
    unordered_set<int> start;
    for (int x : nums) start.insert(x);

    for (int i = 0; i < n; i++) {
      if (!start.count(nums[i] - 1)) {
        int index = nums[i], nowLen = 1;

        while (start.count(++index)) {
          nowLen++;
        }

        maxLen = max(maxLen, nowLen);
      }
    }

    return maxLen;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  cout << obj.longestConsecutive(nums);

  return 0;
}
```

> 第二次遍历就不能再遍历原数组了：
>
> ```cpp
> #include <iostream>
> #include <unordered_set>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int longestConsecutive(vector<int>& nums) {
>         // 直接用nums初始化set
>         unordered_set<int> numSet(nums.begin(), nums.end());
>         int maxLen = 0;
> 
>         // 可以用迭代器遍历set
>         for (int num : numSet) {
>             if (!numSet.count(num - 1)) {
>                 int currentNum = num;
>                 int currentLen = 1;
> 
>                 while (numSet.count(currentNum + 1)) {
>                     currentNum++;
>                     currentLen++;
>                 }
> 
>                 if (currentLen > maxLen) {
>                     maxLen = currentLen;
>                 }
>             }
>         }
> 
>         return maxLen;
>     }
> };
> ```



#### 47.3 解析

这就是最优解，我是看了提示才写出来的，所以不算是做出来了。这个解还是很巧妙的，实际上难点就在怎么开始，而这里直接判断 `nums[i]-1` 在不在集合内，这一步是神来之手。



## 六、区间

### 48. 汇总区间*

#### 48.1 题目

给定一个  **无重复元素** 的 **有序** 整数数组 `nums` 。

区间 `[a,b]` 是从 `a` 到 `b`（包含）的所有整数的集合。

返回 ***恰好覆盖数组中所有数字** 的 **最小有序** 区间范围列表* 。也就是说，`nums` 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个区间但不属于 `nums` 的数字 `x` 。

列表中的每个区间范围 `[a,b]` 应该按如下格式输出：

- `"a->b"` ，如果 `a != b`
- `"a"` ，如果 `a == b`

 

**示例 1：**

```
输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
```

**示例 2：**

```
输入：nums = [0,2,3,4,6,8,9]
输出：["0","2->4","6","8->9"]
解释：区间范围是：
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"
```

 

**提示：**

- `0 <= nums.length <= 20`
- `-231 <= nums[i] <= 231 - 1`
- `nums` 中的所有值都 **互不相同**
- `nums` 按升序排列



#### 48.2 解法

时间复杂度 $O(N)$，空间复杂度 $O(1)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    int n = nums.size(), st = 0;
    if (n == 0) return {};

    vector<string> res;

    // 这里修改了输入参数，虽然比较方便，但是不建议这么做
    nums.push_back(nums.back());
    for (int i = 0; i < n; i++) {
      // 这里如果用+1会溢出，而减一的话，因为是第二个数才开始，而题目要求单调递增且没有相等数，所以第二个数不可能是int的最小值
      if (nums[i] != nums[i + 1] - 1) {
        if (i != st) {
          res.push_back(to_string(nums[st]) + "->" + to_string(nums[i]));
        } else {
          res.push_back(to_string(nums[st]));
        }

        st = i + 1;
      }
    }

    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  vector<string> res = obj.summaryRanges(nums);

  for (const string& s : res) {
    cout << s << endl;
  }

  return 0;
}
```

> 根据上面补充注释的两个问题，可以这么优化：
>
> ```cpp
> #include <iostream>
> #include <string>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<string> summaryRanges(vector<int>& nums) {
>         vector<string> res;
>         int n = nums.size();
>         if (n == 0) return res;
> 
>         for (int i = 0; i < n; ) {
>             int st = i;
>             
>             // 转成longlong避免溢出
>             while (i + 1 < n && (long long)nums[i + 1] - nums[i] == 1) {
>                 i++; //在这迭代，把比较和迭代绑定，这样就不用担心边界问题
>             }
>             
>             if (st != i) {
>                 res.push_back(to_string(nums[st]) + "->" + to_string(nums[i]));
>             } else {
>                 res.push_back(to_string(nums[st]));
>             }
>             
>             i++;
>         }
> 
>         return res;
>     }
> };
> ```



#### 48.3 解析

我的当然也是等效最优解，但是优化版的**分组循环**是这类题目的范式，核心在于外层定位起点，内层定位终点：这样一方面比较可读，不需要记录状态；另一方面彻底告别差一错误，也就是不需要考虑边界问题。



### 49. 合并区间*

#### 49.1 题目

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回 *一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间* 。

 

**示例 1：**

```
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
```

**示例 2：**

```
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
```

**示例 3：**

```
输入：intervals = [[4,7],[1,4]]
输出：[[1,7]]
解释：区间 [1,4] 和 [4,7] 可被视为重叠区间。
```

 

**提示：**

- `1 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 104`



#### 49.2 解法

**时间复杂度**：$O(N \log N)$，**空间复杂度**：$O(\log N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        int n = intervals.size();
        vector<vector<int>> res;

        res.push_back(intervals.front());
        for (int i = 1; i < n; i++) {
            vector<int>& lastRanges = res.back();
            if (lastRanges[0] <= intervals[i][0] && intervals[i][0] <= lastRanges[1]) {
                lastRanges[1] = max(lastRanges[1], intervals[i][1]);
            } else {
                res.push_back(intervals[i]);
            }
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> intervals[i][0] >> intervals[i][1];
    }

    Solution obj;
    vector<vector<int>> res = obj.merge(intervals);

    for (vector<int> x : res) {
        cout << "[" << x[0] << ":" << x[1] << "]" << endl;
    }

    return 0;
}
```

> 经过排序之后，后元素开头不可能小于前元素，所以比较有点多余：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<vector<int>> merge(vector<vector<int>>& intervals) {
>         if (intervals.empty()) {
>             return {};
>         }
> 
>         sort(intervals.begin(), intervals.end(),
>              [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
> 
>         vector<vector<int>> res;
>         res.push_back(intervals[0]);
> 
>         for (int i = 1; i < intervals.size(); i++) {
>             vector<int>& lastRanges = res.back();
>             
>             // 去掉了冗余比较
>             if (intervals[i][0] <= lastRanges[1]) {
>                 lastRanges[1] = max(lastRanges[1], intervals[i][1]);
>             } else {
>                 res.push_back(intervals[i]);
>             }
>         }
> 
>         return res;
>     }
> };
> 
> int main() {
>     ios::sync_with_stdio(false);
>     cin.tie(nullptr);
> 
>     int n;
>     if (cin >> n) {
>         vector<vector<int>> intervals(n, vector<int>(2));
>         for (int i = 0; i < n; i++) {
>             cin >> intervals[i][0] >> intervals[i][1];
>         }
> 
>         Solution obj;
>         vector<vector<int>> res = obj.merge(intervals);
> 
>         // const避免修改、&避免拷贝，一般用在x是数组时（当然包括string）
>         for (const auto& x : res) {
>             cout << "[" << x[0] << ":" << x[1] << "]\n";
>         }
>     }
> 
>     return 0;
> }
> ```



#### 49.3 解析

这就是最优解了，排序没什么好说的，记住lambda的写法即可。





### 50. 插入区间* （@）

#### 50.1 题目

给你一个 **无重叠的** *，*按照区间起始端点排序的区间列表 `intervals`，其中 `intervals[i] = [starti, endi]` 表示第 `i` 个区间的开始和结束，并且 `intervals` 按照 `starti` 升序排列。同样给定一个区间 `newInterval = [start, end]` 表示另一个区间的开始和结束。

在 `intervals` 中插入区间 `newInterval`，使得 `intervals` 依然按照 `starti` 升序排列，且区间之间不重叠（如果有必要的话，可以合并区间）。

返回插入之后的 `intervals`。

**注意** 你不需要原地修改 `intervals`。你可以创建一个新数组然后返回它。

 

**示例 1：**

```
输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]
```

**示例 2：**

```
输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
```

 

**提示：**

- `0 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 105`
- `intervals` 根据 `starti` 按 **升序** 排列
- `newInterval.length == 2`
- `0 <= start <= end <= 105`



#### 50.2 解法

时间复杂度：$O(N)$，空间复杂度$O(N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        if (n == 0) return {newInterval};

        int left = 0, right = n - 1;
        while (right != left) {
            int middle = (left + right) / 2;
            if (newInterval[0] == intervals[middle][0]) {
                right = middle;
                left = middle;
            } else if (newInterval[0] > intervals[middle][0]) {
                if (newInterval[0] <= intervals[middle][1]) {
                    left = middle;
                    right = middle;
                } else {
                    left = middle + 1;
                }
            } else {
                right = middle;
            }
        }

        vector<vector<int>> res;
        bool flag;
        int l;
        for (int i = 0; i < n; i++) {
            if (i < left) {
                res.push_back(intervals[i]);
            } else {
                if (flag) {
                    res.push_back(intervals[i]);
                } else {
                    if (i == left) {
                        if (intervals[i][1] >= newInterval[0]) {
                            l = min(intervals[i][0], newInterval[0]);
                        } else {
                            res.push_back(intervals[i]);
                            l = newInterval[0];
                        }
                    }
                    if (intervals[i][0] > newInterval[1]) {
                        res.push_back({l, newInterval[1]});
                        res.push_back(intervals[i]);
                        flag = true;
                    } else if (intervals[i][1] >= newInterval[1]) {
                        res.push_back({l, intervals[i][1]});
                        flag = true;
                    } else if (i == n - 1) {
                        res.push_back({l, newInterval[1]});
                        flag = true;
                    }
                }
            }
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> intervals[i][0] >> intervals[i][1];
    }

    vector<int> newInterval(2);
    cin >> newInterval[0] >> newInterval[1];

    Solution obj;
    vector<vector<int>> res = obj.insert(intervals, newInterval);

    for (const auto& x : res) {
        cout << "[" << x[0] << ":" << x[1] << "]" << endl;
    }

    return 0;
}
```

> 则二分写得太烂了，而且也没有用。看看优化吧：
>
> ```cpp
> #include <iostream>
> #include <vector>
> #include <algorithm>
> 
> using namespace std;
> 
> class Solution {
> public:
>     vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
>         // 左二分：找到第一个右端点大于等于新区间左端点位置
>         auto compLeft = [](const vector<int>& interval, int val) {
>             return interval[1] < val;
>         };
>         auto itLeft = lower_bound(intervals.begin(), intervals.end(), newInterval[0], compLeft);
> 
>         // 右二分：找到第一个左端点大于新区间右端点位置
>         auto compRight = [](int val, const vector<int>& interval) {
>             return val < interval[0];
>         };
>         auto itRight = upper_bound(itLeft, intervals.end(), newInterval[1], compRight);
> 
>         if (itLeft != itRight) {
>             newInterval[0] = min(newInterval[0], (*itLeft)[0]);
>             newInterval[1] = max(newInterval[1], (*prev(itRight))[1]);
>         }
> 
>         // 使用insert整体插入
>         vector<vector<int>> res;
>         res.insert(res.end(), intervals.begin(), itLeft);
>         res.push_back(newInterval); //保证不遗漏
>         res.insert(res.end(), itRight, intervals.end());
> 
>         return res;
>     }
> };
> ```
>
> 其中：
>
> - **`lower_bound`**：查找 **第一个大于或等于** `val` 的元素。
> - **`upper_bound`**：查找 **第一个大于** `val` 的元素。



#### 50.3 解析

一切的起因就是试图使用二分法加快左边界的查找，之后的逻辑就变得异常复杂。假如不用二分的话，正常是这样的：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int n = intervals.size();
        int i = 0;

        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i]);
            i++;
        }

        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        res.push_back(newInterval);

        while (i < n) {
            res.push_back(intervals[i]);
            i++;
        }

        return res;
    }
};
```

整体就是分三段，并不困难。





### 51. 用最少数量的箭引爆气球*

#### 51.1 题目

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 `points` ，其中`points[i] = [xstart, xend]` 表示水平直径在 `xstart` 和 `xend`之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 **完全垂直** 地射出。在坐标 `x` 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `xstart`，`xend`， 且满足  `xstart ≤ x ≤ xend`，则该气球会被 **引爆** 。可以射出的弓箭的数量 **没有限制** 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 `points` ，*返回引爆所有气球所必须射出的 **最小** 弓箭数* 。

 

**示例 1：**

```
输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用2支箭来爆破:
-在x = 6处射出箭，击破气球[2,8]和[1,6]。
-在x = 11处发射箭，击破气球[10,16]和[7,12]。
```

**示例 2：**

```
输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要4支箭。
```

**示例 3：**

```
输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
- 在x = 2处发射箭，击破气球[1,2]和[2,3]。
- 在x = 4处射出箭，击破气球[3,4]和[4,5]。
```



**提示:**

- `1 <= points.length <= 105`
- `points[i].length == 2`
- `-231 <= xstart < xend <= 231 - 1`



#### 51.2 解法

**时间复杂度**：$O(N \log N)$， **空间复杂度**：$O(\log N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size(), sum = 0;
        if (n == 1) return 1;

        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
        int nowRight = points[0][1];

        for (int i = 1; i < n; i++) {
            if (points[i][0] <= nowRight) {
                nowRight = min(nowRight, points[i][1]);
            } else {
                sum++;
                nowRight = points[i][1];
            }

            if (i == n - 1) {
                sum++;
            }
        }

        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> points(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][1];
    }

    Solution obj;
    cout << obj.findMinArrowShots(points);

    return 0;
}
```

> 可以做成前置判断：
>
> ```cpp
> #include <algorithm>
> #include <iostream>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int findMinArrowShots(vector<vector<int>>& points) {
>         if (points.empty()) return 0;
> 
>         sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
>             return a[0] < b[0];
>         });
> 
>         // 初始直接 1
>         int sum = 1;
>         int nowRight = points[0][1];
> 
>         for (int i = 1; i < points.size(); i++) {
>             // 不重叠再追加
>             if (points[i][0] > nowRight) {
>                 sum++;
>                 nowRight = points[i][1];
>             } else {
>                 nowRight = min(nowRight, points[i][1]);
>             }
>         }
> 
>         return sum;
>     }
> };
> ```



#### 51.3 解析

我这属于“左端点排序”，也算是等效的最优解。但是右端点排序相对更好一点，特别是这种最小覆盖、最多不重叠问题：

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int arrows = 1;
        int currentEnd = points[0][1];

        for (int i = 1; i < points.size(); i++) {
            // 遇到不重叠，就重置有边界与arrows++
            if (points[i][0] > currentEnd) {
                arrows++;
                currentEnd = points[i][1];
            }
        }

        return arrows;
    }
};
```



## 七、栈

### 52. 有效的括号*

#### 52.1 题目

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。

有效字符串需满足：

1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。
3. 每个右括号都有一个对应的相同类型的左括号。

 

**示例 1：**

**输入：**s = "()"

**输出：**true

**示例 2：**

**输入：**s = "()[]{}"

**输出：**true

**示例 3：**

**输入：**s = "(]"

**输出：**false

**示例 4：**

**输入：**s = "([])"

**输出：**true

**示例 5：**

**输入：**s = "([)]"

**输出：**false

 

**提示：**

- `1 <= s.length <= 104`
- `s` 仅由括号 `'()[]{}'` 组成



#### 52.2 解法

时间复杂度 $O(N)$，空间复杂度 $O(N)$

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isValid(string s) {
        stack<char> b;

        for (char c : s) {
            switch (c) {
                case '(':
                case '[':
                case '{': {
                    b.push(c);
                    break;
                }
                case ')':
                case ']':
                case '}': {
                    if (!b.empty() && c == match(b.top())) {
                        b.pop();
                    } else {
                        return false;
                    }
                    break;
                }
            }
        }

        if (b.empty()) {
            return true;
        } else {
            return false;
        }
    }

    char match(char& a) {
        switch (a) {
            case '(':
                return ')';
            case '[':
                return ']';
            case '{':
                return '}';
        }
        return ' ';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    Solution obj;
    cout << obj.isValid(s);

    return 0;
}
```

> 可以做一些琐碎的优化，比如奇数长度不可能是有效的；比如char可以不用传引用（1字节）等：
>
> ```cpp
> #include <iostream>
> #include <stack>
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     bool isValid(string s) {
>         // 奇数检查
>         if (s.length() % 2 != 0) return false;
> 
>         stack<char> st;
>         for (char c : s) {
>             // 期望符号入栈，而不是本身
>             if (c == '(') {
>                 st.push(')');
>             } else if (c == '[') {
>                 st.push(']');
>             } else if (c == '{') {
>                 st.push('}');
>             } else {
>                 if (st.empty() || st.top() != c) {
>                     return false;
>                 }
>                 st.pop();
>             }
>         }
>         
>         // empty本身就是返回true或false
>         return st.empty();
>     }
> };
> ```



#### 52.3 解析

基础题，没什么太多能说的。如果括号（待匹配）类型很多的话，可以用一个额外的数据结构存映射即可，不需要太多重的分支。



### 53. 简化路径*/**

#### 53. 1 题目

给你一个字符串 `path` ，表示指向某一文件或目录的 Unix 风格 **绝对路径** （以 `'/'` 开头），请你将其转化为 **更加简洁的规范路径**。

在 Unix 风格的文件系统中规则如下：

- 一个点 `'.'` 表示当前目录本身。
- 此外，两个点 `'..'` 表示将目录切换到上一级（指向父目录）。
- 任意多个连续的斜杠（即，`'//'` 或 `'///'`）都被视为单个斜杠 `'/'`。
- 任何其他格式的点（例如，`'...'` 或 `'....'`）均被视为有效的文件/目录名称。

返回的 **简化路径** 必须遵循下述格式：

- 始终以斜杠 `'/'` 开头。
- 两个目录名之间必须只有一个斜杠 `'/'` 。
- 最后一个目录名（如果存在）**不能** 以 `'/'` 结尾。
- 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 `'.'` 或 `'..'`）。

返回简化后得到的 **规范路径** 。

 

**示例 1：**

**输入：**path = "/home/"

**输出：**"/home"

**解释：**

应删除尾随斜杠。

**示例 2：**

**输入：**path = "/home//foo/"

**输出：**"/home/foo"

**解释：**

多个连续的斜杠被单个斜杠替换。

**示例 3：**

**输入：**path = "/home/user/Documents/../Pictures"

**输出：**"/home/user/Pictures"

**解释：**

两个点 `".."` 表示上一级目录（父目录）。

**示例 4：**

**输入：**path = "/../"

**输出：**"/"

**解释：**

不可能从根目录上升一级目录。

**示例 5：**

**输入：**path = "/.../a/../b/c/../d/./"

**输出：**"/.../b/d"

**解释：**

`"..."` 在这个问题中是一个合法的目录名。

 

**提示：**

- `1 <= path.length <= 3000`
- `path` 由英文字母，数字，`'.'`，`'/'` 或 `'_'` 组成。
- `path` 是一个有效的 Unix 风格绝对路径。



#### 53.2 解法

时间复杂度 $O(N)$，空间复杂度 $O(N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string simplifyPath(string path) {
        int n = path.size();
        stack<string> paths;

        for (int i = 0; i < n;) {
            if (path[i] == '/') {
                while (i < n && path[++i] == '/');
                if (i == n) break;
                int nameIndex = i;

                while (i < n && path[++i] != '/');
                string dir = path.substr(nameIndex, i - nameIndex);

                if (dir == "..") {
                    if (!paths.empty()) paths.pop();
                    continue;
                }
                if (dir != ".") {
                    paths.push(dir);
                }
            }
        }

        string res = "";
        while (!paths.empty()) {
            res = "/" + paths.top() + res;
            paths.pop();
        }

        return (res == "" ? "/" : res);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string path;
    getline(cin, path);

    Solution obj;
    cout << obj.simplifyPath(path);

    return 0;
}
```

> 分割最好还是用`stringstream`，之前还只是在空格分割中使用：
>
> ```cpp
> #include <iostream>
> #include <sstream>
> #include <string>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     string simplifyPath(string path) {
>         vector<string> dirs;
>         stringstream ss(path);
>         string dir;
> 
>         while (getline(ss, dir, '/')) {
>             if (dir == "" || dir == ".") {
>                 continue;
>             }
>             if (dir == "..") {
>                 if (!dirs.empty()) {
>                     dirs.pop_back();
>                 }
>             } else {
>                 dirs.push_back(dir);
>             }
>         }
> 
>         string res;
>         for (const string& d : dirs) {
>             res += "/" + d;
>         }
> 
>         return res.empty() ? "/" : res;
>     }
> };
> ```
>
> 



#### 53.3 解析

这个问题其实是遍历时需要先入后出，转化字符串时需要先入先出，这个时候单纯的`stack`限制太大了，反而使用`vector`能完美模拟它。



### 54. 最小栈*（@）

#### 54.1 题目

设计一个支持 `push` ，`pop` ，`top` 操作，并能在常数时间内检索到最小元素的栈。

实现 `MinStack` 类:

- `MinStack()` 初始化堆栈对象。
- `void push(int val)` 将元素val推入堆栈。
- `void pop()` 删除堆栈顶部的元素。
- `int top()` 获取堆栈顶部的元素。
- `int getMin()` 获取堆栈中的最小元素。

 

**示例 1:**

```
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
```

 

**提示：**

- `-231 <= val <= 231 - 1`
- `pop`、`top` 和 `getMin` 操作总是在 **非空栈** 上调用
- `push`, `pop`, `top`, and `getMin`最多被调用 `3 * 104` 次



#### 54.2 解法

**时间复杂度**：$O(1)$，**空间复杂度**：$O(N)$。

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MinStack {
private:
    vector<int> stack;
    vector<int> minStack;

public:
    MinStack() {}

    void push(int val) {
        stack.push_back(val);
        if (minStack.empty() || val <= minStack.back()) {
            minStack.push_back(val);
        }
    }

    void pop() {
        if (stack.back() == minStack.back()) {
            minStack.pop_back();
        }
        stack.pop_back();
    }

    int top() {
        return stack.back();
    }

    int getMin() {
        return minStack.back();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        MinStack minStack;
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;

            if (cmd == "MinStack") {
                cout << "null ";
            } else if (cmd == "push") {
                int val;
                cin >> val;
                minStack.push(val);
                cout << "null ";
            } else if (cmd == "pop") {
                minStack.pop();
                cout << "null ";
            } else if (cmd == "top") {
                cout << minStack.top() << " ";
            } else if (cmd == "getMin") {
                cout << minStack.getMin() << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
```



#### 54.3 解析

这道题最关键是利用一个**辅助栈（向量）**，因为栈的先入后出的特点，如果后进的元素比前一个大，那么它的出栈不会影响最小值，所以不需要存它；反之则需要存，这就是`minStack`。

此外，还有一种高内聚的方案，理论上差不多，工程上可能更安全：

```cpp
#include <algorithm>
#include <vector>

using namespace std;

class MinStack {
private:
    // pair结构，类似定长为2的数组
    vector<pair<int, int>> st;

public:
    MinStack() {}

    void push(int val) {
        if (st.empty()) {
            st.push_back({val, val});
        } else {
            st.push_back({val, min(val, st.back().second)});
        }
    }

    void pop() {
        st.pop_back();
    }

    int top() {
        return st.back().first;
    }

    int getMin() {
        return st.back().second;
    }
};
```



### 55. 逆波兰表达式求值*

#### 55.1 题目

给你一个字符串数组 `tokens` ，表示一个根据 [逆波兰表示法](https://baike.baidu.com/item/逆波兰式/128437) 表示的算术表达式。

请你计算该表达式。返回一个表示表达式值的整数。

**注意：**

- 有效的算符为 `'+'`、`'-'`、`'*'` 和 `'/'` 。
- 每个操作数（运算对象）都可以是一个整数或者另一个表达式。
- 两个整数之间的除法总是 **向零截断** 。
- 表达式中不含除零运算。
- 输入是一个根据逆波兰表示法表示的算术表达式。
- 答案及所有中间计算结果可以用 **32 位** 整数表示。

 

**示例 1：**

```
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
```

**示例 2：**

```
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
```

**示例 3：**

```
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
```

 

**提示：**

- `1 <= tokens.length <= 104`
- `tokens[i]` 是一个算符（`"+"`、`"-"`、`"*"` 或 `"/"`），或是在范围 `[-200, 200]` 内的一个整数

 

**逆波兰表达式：**

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

- 平常使用的算式则是一种中缀表达式，如 `( 1 + 2 ) * ( 3 + 4 )` 。
- 该算式的逆波兰表达式写法为 `( ( 1 2 + ) ( 3 4 + ) * )` 。

逆波兰表达式主要有以下两个优点：

- 去掉括号后表达式无歧义，上式即便写成 `1 2 + 3 4 + * `也可以依据次序计算出正确结果。
- 适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中



#### 55.2 解法

**时间复杂度**：$O(N)$，**空间复杂度**：$O(N)$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        vector<int> stack;

        for (int i = 0; i < n; i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int b = stack.back();
                stack.pop_back();
                int a = stack.back();
                stack[stack.size() - 1] = calculate(a, b, tokens[i]);
            } else {
                stack.push_back(stoi(tokens[i]));
            }
        }

        return stack.back();
    }

    int calculate(int a, int b, string cal) {
        if (cal == "*") {
            return a * b;
        }
        if (cal == "/") {
            return a / b;
        }
        if (cal == "+") {
            return a + b;
        }
        if (cal == "-") {
            return a - b;
        }

        return 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    Solution obj;
    cout << obj.evalRPN(s);

    return 0;
}
```

> 在数字判断上的优化：
>
> ```cpp
> #include <iostream>
> #include <string>
> #include <vector>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int evalRPN(vector<string>& tokens) {
>         vector<long long> st;
>         
>         for (const string& s : tokens) {
>             // 如果负数，条件一；如果正数，条件二
>             if (s.size() > 1 || isdigit(s[0])) {
>                 st.push_back(stoll(s));
>             } else {
>                 long long b = st.back();
>                 st.pop_back();
>                 long long a = st.back();
>                 
>                 // 直接用back就行
>                 if (s == "+") st.back() = a + b;
>                 else if (s == "-") st.back() = a - b;
>                 else if (s == "*") st.back() = a * b;
>                 else if (s == "/") st.back() = a / b;
>             }
>         }
>         
>         return st.back();
>     }
> };
> ```



#### 55.3 解析

这道题就是用栈做的，也是逆波兰表达式的本质。不过此外，还有一种比较优雅的解法：

```cpp
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        // 计算符号到函数（lambda）的映射
        unordered_map<string, function<long long(long long, long long)>> ops = {
            {"+", [](long long a, long long b) { return a + b; }},
            {"-", [](long long a, long long b) { return a - b; }},
            {"*", [](long long a, long long b) { return a * b; }},
            {"/", [](long long a, long long b) { return a / b; }}
        };

        vector<long long> st;

        for (const string& s : tokens) {
            // 由于map记录所有符号，直接count，十分巧妙
            if (ops.count(s)) {
                long long b = st.back();
                st.pop_back();
                long long a = st.back();
                st.back() = ops[s](a, b);
            } else {
                st.push_back(stoll(s));
            }
        }

        return st.back();
    }
};
```



### 56. 基本计算器*

#### 56.1 题目

给你一个字符串表达式 `s` ，请你实现一个基本计算器来计算并返回它的值。

注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 `eval()` 。

 

**示例 1：**

```
输入：s = "1 + 1"
输出：2
```

**示例 2：**

```
输入：s = " 2-1 + 2 "
输出：3
```

**示例 3：**

```
输入：s = "(1+(4+5+2)-3)+(6+8)"
输出：23
```

 

**提示：**

- `1 <= s.length <= 3 * 105`
- `s` 由数字、`'+'`、`'-'`、`'('`、`')'`、和 `' '` 组成
- `s` 表示一个有效的表达式
- `'+'` 不能用作一元运算(例如， `"+1"` 和 `"+(2 + 3)"` 无效)
- `'-'` 可以用作一元运算(即 `"-1"` 和 `"-(2 + 3)"` 是有效的)
- 输入中不存在两个连续的操作符
- 每个数字和运行的计算将适合于一个有符号的 32位 整数



#### 56.2 解法

时间复杂度：接近 **O(N)**，空间复杂度：**O(N)**

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int calculate(string s) {
        int n = s.size();
        long long sum = 0;
        bool sign = true;
        vector<bool> bracket;

        for (int i = 0; i < n; i++) {
            if (s[i] == '-' || s[i] == '+') {
                if (!bracket.empty() && !bracket.back()) {
                    sign = s[i] == '-';
                } else {
                    sign = s[i] == '+';
                }
            } else if (s[i] == '(') {
                int index = i;
                while (index > 0 && s[--index] == ' ');
                bracket.push_back(sign);
            } else if (s[i] == ')') {
                bracket.pop_back();
            } else if (s[i] == ' ') {
                continue;
            } else {
                int st = i;
                while (i < n - 1 && isdigit(s[++i]));
                long long num;
                if (i == n - 1) {
                    num = stol(s.substr(st, n - st));
                    sum += (sign ? num : -num);
                    break;
                } else {
                    num = stol(s.substr(st, i - st));
                    sum += (sign ? num : -num);
                    i--;
                }
            }
        }

        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    Solution obj;
    cout << obj.calculate(s);
    return 0;
}
```

> 才发现我那个`while`是残留的旧方法的代码，没什么用；另外，`stoi`也拖累了速度：
>
> ```cpp
> #include <iostream>
> #include <stack>
> #include <string>
> 
> using namespace std;
> 
> class Solution {
> public:
>     int calculate(string s) {
>         // 默认先置一个正号，节省了后面的一堆判断
>         stack<int> ops;
>         ops.push(1);
>         int sign = 1;
>         int res = 0;
>         int n = s.length();
>         int i = 0;
>         
>         while (i < n) {
>             if (s[i] == ' ') {
>                 i++;
>             } else if (s[i] == '+') {
>                 sign = ops.top();
>                 i++;
>             } else if (s[i] == '-') {
>                 sign = -ops.top();
>                 i++;
>             } else if (s[i] == '(') {
>                 ops.push(sign);
>                 i++;
>             } else if (s[i] == ')') {
>                 ops.pop();
>                 i++;
>             } else {
>                 long long num = 0;
>                 while (i < n && isdigit(s[i])) {
>                     num = num * 10 + (s[i] - '0');
>                     i++;
>                 }
>                 res += sign * num;
>             }
>         }
>         return res;
>     }
> };
> ```



#### 56.3 解析

算是等效最优解，这道题的关键在于注意到这是只有加减的计算，也就是只要展开括号即可。此外还有一种更通用的**双栈状态保存法**：

- 当左括号 ，将**当前的累加结果 `res`** 和 **括号前的符号 `sign`** 压入栈中封存起来，然后把 `res` 清零，计算下一层括号结果。
-  等遇到右括号 ，再把存起来的老结果和老符号弹出来，跟刚刚算出的括号内的值合并。

即：

```cpp
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int res = 0;
        int sign = 1;
        int n = s.length();
        int i = 0;

        while (i < n) {
            if (isdigit(s[i])) {
                long long num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                res += sign * num;
            } else if (s[i] == '+') {
                sign = 1;
                i++;
            } else if (s[i] == '-') {
                sign = -1;
                i++;
            } else if (s[i] == '(') {
                // 括号前压栈
                st.push(res);
                st.push(sign);
                res = 0;
                sign = 1;
                i++;
            } else if (s[i] == ')') {
                // 括号后合并
                int prevSign = st.top();
                st.pop();
                int prevRes = st.top();
                st.pop();
                res = prevRes + prevSign * res;
                i++;
            } else {
                i++;
            }
        }
        return res;
    }
};
```

