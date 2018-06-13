/*
679. 24 Game
DescriptionHintsSubmissionsDiscussSolution
You have 4 cards each containing a number from 1 to 9. 
You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.

Example 1:
Input: [4, 1, 8, 7]
Output: True
Explanation: (8-4) * (7-1) = 24
Example 2:
Input: [1, 2, 1, 2]
Output: False
Note:
The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
Every operation done is between two numbers. In particular, we cannot use - as a unary operator. For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.
Seen this question in a real interview before?  

*/

//大神之作ミﾟДﾟ彡

//python3
class Solution:
    def judgePoint24(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        bad = '떢븻각걎냇갅갸꺚뵟숣욄뵴뵞뤼갈갌뤔떌옊메늄숭캸긶꺛옖갍뇐쩢곴듇걯궄옕왹눞솴걃끗긬땉궿가쌀낐걄숤뺴늘걘꽸숢걂갋갃쫐꼔솾쩡쇔솿끛뤜간븺쩬웨딴옠뤛갂뵪덠놤빐옋귒늂갰갖놥궾갆옌뼘묰거갎긷낤겼'
        return chr(int(''.join(map(str, sorted(nums)))) + 42921) not in bad
//Submission Result: Accepted 

class Solution:
    def judgePoint24(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        bad = '对撒剘劥圞剜劏哱掶桺泛揋掵従剟剣彫寣污悫壛梄甏咍哲汭剤堧点卋嬞勆叛汬泐塵栋劚嚮咃宠吖剗楗囧力桻攋壯劯嗏桹劙剢剚焧啫栕炸栫栖嚲彳剛撑烃洿宋汷彲剙揁妷埻撧汢吩壙劇剭埼吕剝汣敯憇勇剥咎囻匓'
        return chr(int(''.join(map(str, sorted(nums)))) + 19968) not in bad
//Submission Result: Accepted 








        

class Solution {
public:
    bool judgePoint24(vector<int>& A) {
        sort(A.begin(),A.end());
        do{
            if (go(A[0],A[1],A[2],A[3])) 
            	return true;
        } while (next_permutation(A.begin(),A.end()));
        return false;
    }
private:
    bool go(double a, double b, double c, double d) {
        return
            go(a+b,c,d) || go(a-b,c,d) || go(a*b,c,d) || (b&&go(a/b,c,d)) ||
            go(a,b+c,d) || go(a,b-c,d) || go(a,b*c,d) || (c&&go(a,b/c,d)) ||
            go(a,b,c+d) || go(a,b,c-d) || go(a,b,c*d) || (d&&go(a,b,c/d));
    }
    bool go(double a, double b, double c){
        return
            go(a+b,c) || go(a-b,c) || go(a*b,c) || (b&&go(a/b,c)) ||
            go(a,b+c) || go(a,b-c) || go(a,b*c) || (c&&go(a,b/c));
    }
    bool go(double a, double b){
        return abs(a+b-24.0)<0.0001 || abs(a-b-24.0)<0.0001 
        || abs(a*b-24.0)<0.0001 || (b&&abs(a/b-24.0)<0.0001);
    }
};
//Submission Result: Accepted 