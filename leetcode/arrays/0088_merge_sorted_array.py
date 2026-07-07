class Solution(object):
    def merge(self, nums1, m, nums2, n):
        if(m == 0):
            for i in range(len(nums1)):
                nums1[i] = nums2[i]
        elif(n == 0):
            nums1 = nums1[0:m]
        else:
            s = nums1[0:m] + nums2[0:n]
            s.sort()
            for i in range(len(nums1)):
                nums1[i] = s[i]
            print(nums1)

        