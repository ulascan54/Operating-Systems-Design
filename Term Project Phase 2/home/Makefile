all: test1 test2 test3

test1: test1-exes test1-u1 test1-u2  test1-run test1-avg test1-mse test1-mse-avg clear-o kill-all

test1-exes:
	gcc -o u1p1.o test.c
	gcc -o u1p2.o test.c
	gcc -o u2p1.o test.c

test1-u1:
	su u1 -c './u1p1.o &'
	su u1 -c './u1p2.o &'

test1-u2:
	su u2 -c './u2p1.o &'

test1-run:
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		top -d 0.2 -n 100 -b > result/test1/${FOLDER}/SchedTop$$i.txt ; \
	done 

test1-avg:
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		cat result/test1/${FOLDER}/SchedTop$$i.txt | grep 'u1p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test1/${FOLDER}/u1p1avg.txt ; \
		cat result/test1/${FOLDER}/SchedTop$$i.txt | grep 'u1p2.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test1/${FOLDER}/u1p2avg.txt ; \
		cat result/test1/${FOLDER}/SchedTop$$i.txt | grep 'u2p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test1/${FOLDER}/u2p1avg.txt ; \
	done 

test1-mse:
	grep "average" result/test1/${FOLDER}/u1p1avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=25;} else {x=33.33;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test1/${FOLDER}/test1MSE.txt
	grep "average" result/test1/${FOLDER}/u1p2avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=25;} else {x=33.33;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test1/${FOLDER}/test1MSE.txt
	grep "average" result/test1/${FOLDER}/u2p1avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=50;} else {x=33.33;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test1/${FOLDER}/test1MSE.txt

test1-mse-avg:
	grep "mse" result/test1/${FOLDER}/test1MSE.txt | awk 'BEGIN{sum=0; n=0}{sum=sum+$$2; n=n+1}END{print "avg-mse",sum/n}' >> result/test1/${FOLDER}/test1MSE.txt


test2: test2-exes test2-u1 test2-u2 test2-u3  test2-run test2-avg test2-mse test2-mse-avg clear-o kill-all

test2-exes:
	gcc -o u1p1.o test.c
	gcc -o u1p2.o test.c
	gcc -o u2p1.o test.c
	gcc -o u2p2.o test.c
	gcc -o u3p1.o test.c
	gcc -o u3p2.o test.c

test2-u1:
	su u1 -c './u1p1.o &'
	su u1 -c './u1p2.o &'

test2-u2:
	su u2 -c './u2p1.o &'
	su u2 -c './u2p2.o &'

test2-u3:
	su u3 -c './u3p1.o &'
	su u3 -c './u3p2.o &'

test2-run:
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		top -d 0.4 -n 100 -b > result/test2/${FOLDER}/SchedTop$$i.txt ; \
	done 

test2-avg:
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		cat result/test2/${FOLDER}/SchedTop$$i.txt | grep 'u1p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test2/${FOLDER}/u1p1avg.txt ; \
		cat result/test2/${FOLDER}/SchedTop$$i.txt | grep 'u1p2.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test2/${FOLDER}/u1p2avg.txt ; \
		cat result/test2/${FOLDER}/SchedTop$$i.txt | grep 'u2p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test2/${FOLDER}/u2p1avg.txt ; \
		cat result/test2/${FOLDER}/SchedTop$$i.txt | grep 'u2p2.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test2/${FOLDER}/u2p2avg.txt ; \
		cat result/test2/${FOLDER}/SchedTop$$i.txt | grep 'u3p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test2/${FOLDER}/u3p1avg.txt ; \
		cat result/test2/${FOLDER}/SchedTop$$i.txt | grep 'u3p2.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test2/${FOLDER}/u3p2avg.txt ; \
	done 

test2-mse:
	grep "average" result/test2/${FOLDER}/u1p1avg.txt | awk 'BEGIN{sum=0; n=0; x=16.67;}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test2/${FOLDER}/test2MSE.txt
	grep "average" result/test2/${FOLDER}/u1p2avg.txt | awk 'BEGIN{sum=0; n=0; x=16.67;}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test2/${FOLDER}/test2MSE.txt
	grep "average" result/test2/${FOLDER}/u2p1avg.txt | awk 'BEGIN{sum=0; n=0; x=16.67;}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test2/${FOLDER}/test2MSE.txt
	grep "average" result/test2/${FOLDER}/u2p2avg.txt | awk 'BEGIN{sum=0; n=0; x=16.67;}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test2/${FOLDER}/test2MSE.txt
	grep "average" result/test2/${FOLDER}/u3p1avg.txt | awk 'BEGIN{sum=0; n=0; x=16.67;}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test2/${FOLDER}/test2MSE.txt
	grep "average" result/test2/${FOLDER}/u3p2avg.txt | awk 'BEGIN{sum=0; n=0; x=16.67;}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test2/${FOLDER}/test2MSE.txt

test2-mse-avg:
	grep "mse" result/test2/${FOLDER}/test2MSE.txt | awk 'BEGIN{sum=0; n=0}{sum=sum+$$2; n=n+1}END{print "avg-mse",sum/n}' >> result/test2/${FOLDER}/test2MSE.txt

test3: test3-exes test3-u1 test3-u2 test3-u3  test3-run test3-avg test3-mse test3-mse-avg clear-o kill-all

test3-exes:
	gcc -o u1p1.o test.c
	gcc -o u2p1.o test.c
	gcc -o u2p2.o test.c
	gcc -o u3p1.o test.c
	gcc -o u3p2.o test.c
	gcc -o u3p3.o test.c

test3-u1:
	su u1 -c './u1p1.o &'

test3-u2:
	su u2 -c './u2p1.o &'
	su u2 -c './u2p2.o &'

test3-u3:
	su u3 -c './u3p1.o &'
	su u3 -c './u3p2.o &'
	su u3 -c './u3p3.o &'

test3-run:
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		top -d 0.4 -n 100 -b > result/test3/${FOLDER}/SchedTop$$i.txt ; \
	done 

test3-avg:
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		cat result/test3/${FOLDER}/SchedTop$$i.txt | grep 'u1p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test3/${FOLDER}/u1p1avg.txt ; \
		cat result/test3/${FOLDER}/SchedTop$$i.txt | grep 'u2p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test3/${FOLDER}/u2p1avg.txt ; \
		cat result/test3/${FOLDER}/SchedTop$$i.txt | grep 'u2p2.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test3/${FOLDER}/u2p2avg.txt ; \
		cat result/test3/${FOLDER}/SchedTop$$i.txt | grep 'u3p1.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test3/${FOLDER}/u3p1avg.txt ; \
		cat result/test3/${FOLDER}/SchedTop$$i.txt | grep 'u3p2.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test3/${FOLDER}/u3p2avg.txt ; \
		cat result/test3/${FOLDER}/SchedTop$$i.txt | grep 'u3p3.o' | awk 'BEGIN{total=0;num=0}{num=num+1;total=total+$$9;print $$9}END{avg=total/num;print "total=", total;print "average=", avg}' >> result/test3/${FOLDER}/u3p3avg.txt ; \
	done 

test3-mse:
	grep "average" result/test3/${FOLDER}/u1p1avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=33.33;} else {x=16.67;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test3/${FOLDER}/test3MSE.txt
	grep "average" result/test3/${FOLDER}/u2p1avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=16.67;} else {x=16.67;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test3/${FOLDER}/test3MSE.txt
	grep "average" result/test3/${FOLDER}/u2p2avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=16.67;} else {x=16.67;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test3/${FOLDER}/test3MSE.txt
	grep "average" result/test3/${FOLDER}/u3p1avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=11.11;} else {x=16.67;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test3/${FOLDER}/test3MSE.txt
	grep "average" result/test3/${FOLDER}/u3p2avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=11.11;} else {x=16.67;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test3/${FOLDER}/test3MSE.txt
	grep "average" result/test3/${FOLDER}/u3p3avg.txt | awk 'BEGIN{sum=0; n=0; if ( "${FOLDER}" == "fair" ) {x=11.11;} else {x=16.67;}}{sum=sum+(($$2-x)*($$2-x)); n=n+1}END{print "mse", sum/n}' >> result/test3/${FOLDER}/test3MSE.txt

test3-mse-avg:
	grep "mse" result/test3/${FOLDER}/test3MSE.txt | awk 'BEGIN{sum=0; n=0}{sum=sum+$$2; n=n+1}END{print "avg-mse",sum/n}' >> result/test3/${FOLDER}/test3MSE.txt

kill-all:
	ps aux | grep -e "\.o$$" | awk '{print $$2}' | xargs kill

clear: clear-o clear-txt kill-all

clear-o:
	rm -f *.o

clear-txt:
	rm -f *.txt
	rm -f result/test1/${FOLDER}/*.txt
	rm -f result/test2/${FOLDER}/*.txt
	rm -f result/test3/${FOLDER}/*.txt