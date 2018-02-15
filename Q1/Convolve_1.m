function [output] = Conv1d(input,filt)
len_ipt = size(input,2);
len_fil = size(filt,2);
start_fil = 1;
end_fil = len_fil;
% reverse
while(start_fil < end_fil)
    temp = filt(start_fil);
    filt(start_fil) = filt(end_fil);
    filt(end_fil) = temp;
    start_fil = start_fil + 1;
    end_fil = end_fil - 1;
end
% padding
output = zeros(1, len_fil - 1 + len_ipt);
for k = 1:len_fil - 1
    input = [0 input 0];
end
% convolution
for k = 1:len_fil - 1 + len_ipt
    sum = 0;
    for t = 1:len_fil
        sum = sum + input(k + t - 1) * filt(t);
    end
    output(k) = sum;
end
end

