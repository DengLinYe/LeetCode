# LeetCode Log

> - 先以《面试经典150题》开始，每日两题预计五月中结束，此后题目再议。
> - 题目后的`*`个数表示难度，一般我能做出等效最优解的题目，不视为难题，即 *；而若能解出但不是最优，则 **；若无法解出，则 \*\*\*。特别地，如果做到了等效最优解，但是相对不够好，则 \*/\*\*

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

   
