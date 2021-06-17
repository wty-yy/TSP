fid = fopen('48.in', 'r');
n = fscanf(fid, '%d', 1)
A = fscanf(fid, '%f', [3,n])

for i = 1 : n
    plot(A(2, i),A(3,i),'.','Color','g','MarkerSize',15);
    hold on;
end
x = fscanf(fid, '%d', 1);
for i = 1 : x
    m = fscanf(fid, '%d', 1);
    X = fscanf(fid, '%f', m);
    Y = fscanf(fid, '%f', m);
    plot(X, Y);
end
fclose(fid);