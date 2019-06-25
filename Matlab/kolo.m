a_last = 0; b_last = 0; c_last = 0;
a = 0; b = 0; c = 0;

for t = 0:0.1:10 
    a = round(200*sin(t)) - a_last;
    b = round(200*sin(t)) - b_last;
    c = round(200*sin(t)) - c_last;
    
    fprintf(s, 'a %d b %d c %d\n', [a,b,c]);
    
    while(s.BytesAvailable == 0);end
    while(s.BytesAvailable > 0)
        fscanf(s);
    end

    a_last = a;
    b_last = b;
    c_last = c;
end

