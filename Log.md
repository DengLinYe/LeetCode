# LeetCode Log

> - 先以《面试经典150题》开始，每日两题预计五月中结束，此后题目再议。
> - 题目后的`*`个数表示难度，一般我能做出等效最优解的题目，不视为难题。

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

   