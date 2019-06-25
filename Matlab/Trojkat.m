a = [0 0 400 400 -400 -400];
b = [400 400 -400 -400 0 0];
c = [-400 -400 0 0 400 400];

a = [a 16 a 16 a 16 a 16];
b = [b 16 b 16 b 16 b 16];
c = [c 16 c 16 c 16 c 16];

a = [a a a a a a a a a a a a 3200];
b = [b b b b b b b b b b b b 3200];
c = [c c c c c c c c c c c c 3200];

for i = 1:length(a)
    
    if(a(i) == 16 || a(i) == 3200)
        fprintf(s,sprintf("a %d b %d c %d e 0",a(i),b(i),c(i)));
        while(s.BytesAvailable == 0);end
        while(s.BytesAvailable > 0)
            fscanf(s);
        end
    else
        fprintf(s,sprintf("a %d b %d c %d e 60",a(i),b(i),c(i)));
        while(s.BytesAvailable == 0);end
        while(s.BytesAvailable > 0)
            fscanf(s);
        end
    end
    
end

% fprintf(s,sprintf("a -500 b -500 c -500 e 0");