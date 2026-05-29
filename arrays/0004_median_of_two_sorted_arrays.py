class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:

        i = 0
        j = 0
        val = 0
        if (len(nums1) == 0 and len(nums2)==0):
            actual = 0
        elif(len(nums1)== 0):
            actual = nums2[j]
            j+=1
        elif(len(nums2)==0):
            actual = nums1[i]
            i+=1

        elif nums1[i] < nums2[j]:
            actual = nums1[i]
            i += 1
        else:
            actual = nums2[j]
            j += 1

        p = (len(nums1) + len(nums2)) // 2

        while True:
            ant = actual

            if i < len(nums1) and j < len(nums2):

                if nums1[i] < nums2[j]:

                    if actual <= nums1[i]:
                        actual = nums1[i]
                        i += 1

                else:

                    if actual <= nums2[j]:
                        actual = nums2[j]
                        j += 1

            elif i < len(nums1):

                if actual <= nums1[i]:
                    actual = nums1[i]
                    i += 1

            elif j < len(nums2):

                if actual <= nums2[j]:
                    actual = nums2[j]
                    j += 1

            val += 1

            if val >= p:
                break

        if (len(nums1) + len(nums2)) % 2 == 1:
            return actual

        else:

            

            return (actual+ant)/2

        