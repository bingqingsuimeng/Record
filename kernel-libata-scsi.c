mw.b 0x82000000 0xff 0x480000; tftp 0x82000000 hi3520d/uImage_3520d; bootm 0x82000000

mount -o nolock 192.168.1.56:/mnt/nfs /mnt
cd /mnt/hi3520d
mkdir /root/rec/a1
mkdir /root/rec/a2
mkdir /root/rec/a3
mkdir /root/rec/a4
mount -o sync /dev/sda1 /root/rec/a1
mount -o sync /dev/sda2 /root/rec/a2
mount -o sync /dev/sda3 /root/rec/a3
mount -o sync /dev/sda4 /root/rec/a4

./copy_file /root/rec/a3/fly00000.ifv /root/rec/a1/fly00059.ifv 50 60 

./copy_file /mnt/hi3520d/0.ifv /root/rec/a1/fly00058.ifv
./copy_file /mnt/hi3520d/1.ifv /root/rec/a1/fly00058.ifv

libata-eh.c
	void ata_scsi_error(struct Scsi_Host *host)
libata-scsi.c
	static void ata_to_sense_error(unsigned id, u8 drv_stat, u8 drv_err, u8 *sk,
			       u8 *asc, u8 *ascq, int verbose)
sd.h
	#define SD_MAX_RETRIES		1
sd.c
	unsigned int g_ata_error_count = 0;
	EXPORT_SYMBOL(g_ata_error_count);	
	
	static int sd_prep_fn(struct request_queue *q, struct request *rq)
	

struct request_queue *scsi_alloc_queue(struct scsi_device *sdev)
{
	struct request_queue *q;

	q = __scsi_alloc_queue(sdev->host, scsi_request_fn);
	if (!q)
		return NULL;

	blk_queue_prep_rq(q, scsi_prep_fn);
	blk_queue_softirq_done(q, scsi_softirq_done);
	blk_queue_rq_timed_out(q, scsi_times_out);
	blk_queue_lld_busy(q, scsi_lld_busy);
	return q;
}

struct Scsi_Host *scsi_host_alloc(struct scsi_host_template *sht, int privsize)
	shost->ehandler = kthread_run(scsi_error_handler, shost,"scsi_eh_%d", shost->host_no);
	
	/**  �������߳�
	 * scsi_error_handler - SCSI error handler thread
	 * @data:	Host for which we are running.
	 *
	 * Notes:
	 *    This is the main error handling loop.  This is run as a kernel thread
	 *    for every SCSI host and handles all error handling activity.
	 */
	int scsi_error_handler(void *data)
	{
		...
		if (shost->transportt->eh_strategy_handler)
			shost->transportt->eh_strategy_handler(shost);
		...
	}
	


	
	timeout_count=
	custommp4_write_data
	hard resetting link
ԭ��SATA����
#define SD
_MAX_RETRIES		5
	28������	
#define SD_MAX_RETRIES		1 
	18������		
#define SD_MAX_RETRIES		0
	12������

��sata�� 10������
�ε�Դ�� 
#define SD_MAX_RETRIES		1 --- tv1:20.181703, tv2:31.558210
								tv1:67.757040, tv2:78.964472
#define SD_MAX_RETRIES		5 --- tv1:23.154580, tv2:34.370416
								tv1:21.146733, tv2:32.506507


ȫ���ܰ� USBתSATA
#define SD_MAX_RETRIES		5
	tv1:43.942926, tv2:59.659930		
#define SD_MAX_RETRIES		1 
	tv1:36.438837, tv2:48.194967
	tv1:49.221290, tv2:66.477123
	tv1:55.848487, tv2:60.274517	
#define SD_MAX_RETRIES		0
	Ӳ�̾�����ⲻ��
	
��sata�� ��ӡ��usb 1-1: USB disconnect, device number 2�������̷���
�ε�Դ�� ͬ��

#define SD_TIMEOUT		(30 * HZ)
	tv1:137.245698, tv2:145.288544
		
HD Tune Pro: KingsharKSHDD100 ����ɨ��

ɨ������   : 19 gB
�𻵵Ŀ� : 22.6 %
����ʱ��   : 14:32:56
1  ������ 5191 MB (LBA 10633164)
2  ������ 5221 MB (LBA 10692940)
3  ������ 6443 MB (LBA 13195743)
4  ������ 6452 MB (LBA 13214943)
5  ������ 6515 MB (LBA 13343839)
6  ������ 6521 MB (LBA 13356255)
7  ������ 6532 MB (LBA 13378783)
8  ������ 6540 MB (LBA 13394399)
9  ������ 6547 MB (LBA 13409887)
10  ������ 6567 MB (LBA 13451103)
11  ������ 6577 MB (LBA 13470047)
12  ������ 6586 MB (LBA 13488735)
13  ������ 6586 MB (LBA 13488863)
14  ������ 6587 MB (LBA 13492191)
15  ������ 7663 MB (LBA 15694687)
16  ������ 7665 MB (LBA 15698015)
17  ������ 7665 MB (LBA 15698143)
18  ������ 7665 MB (LBA 15698271)
19  ������ 7668 MB (LBA 15704671)
20  ������ 7672 MB (LBA 15714271)
21  ������ 7673 MB (LBA 15714399)
22  ������ 7677 MB (LBA 15723103)
23  ������ 7678 MB (LBA 15726559)
24  ������ 7680 MB (LBA 15729631)
25  ������ 7680 MB (LBA 15729759)
26  ������ 7683 MB (LBA 15736159)
27  ������ 7683 MB (LBA 15736287)
28  ������ 7686 MB (LBA 15742687)
29  ������ 7692 MB (LBA 15754591)
30  ������ 7692 MB (LBA 15754719)
31  ������ 7695 MB (LBA 15761119)
32  ������ 7695 MB (LBA 15761247)
33  ������ 7697 MB (LBA 15764319)
34  ������ 7697 MB (LBA 15764447)
35  ������ 7698 MB (LBA 15767519)
36  ������ 7720 MB (LBA 15811679)
37  ������ 7722 MB (LBA 15814751)
38  ������ 7722 MB (LBA 15814879)
39  ������ 7723 MB (LBA 15817951)
40  ������ 7723 MB (LBA 15818079)
41  ������ 7725 MB (LBA 15821279)
42  ������ 7726 MB (LBA 15824479)
43  ������ 7735 MB (LBA 15843039)
44  ������ 7737 MB (LBA 15846239)
45  ������ 7737 MB (LBA 15846367)
46  ������ 7742 MB (LBA 15855967)
47  ������ 7748 MB (LBA 15868767)
48  ������ 7758 MB (LBA 15890015)
49  ������ 7758 MB (LBA 15890271)
50  ������ 7760 MB (LBA 15893343)
51  ������ 7768 MB (LBA 15909087)
52  ������ 7768 MB (LBA 15909215)
53  ������ 7769 MB (LBA 15912287)
54  ������ 7769 MB (LBA 15912415)
55  ������ 7777 MB (LBA 15928415)
56  ������ 7779 MB (LBA 15931615)
57  ������ 7780 MB (LBA 15934943)
58  ������ 7783 MB (LBA 15940831)
59  ������ 7786 MB (LBA 15946975)
60  ������ 7786 MB (LBA 15947103)
61  ������ 7788 MB (LBA 15950175)
62  ������ 7788 MB (LBA 15950303)
63  ������ 7789 MB (LBA 15953503)
64  ������ 7795 MB (LBA 15965791)
65  ������ 7797 MB (LBA 15969247)
66  ������ 7803 MB (LBA 15981535)
67  ������ 7803 MB (LBA 15981791)
68  ������ 7805 MB (LBA 15984863)
69  ������ 7812 MB (LBA 16000735)
70  ������ 7817 MB (LBA 16009823)
71  ������ 7818 MB (LBA 16013279)
72  ������ 7823 MB (LBA 16022495)
73  ������ 7825 MB (LBA 16025951)
74  ������ 7829 MB (LBA 16035039)
75  ������ 7829 MB (LBA 16035167)
76  ������ 7829 MB (LBA 16035295)
77  ������ 7831 MB (LBA 16038495)
78  ������ 7831 MB (LBA 16038623)
79  ������ 7832 MB (LBA 16041951)
80  ������ 7845 MB (LBA 16066911)
81  ������ 7846 MB (LBA 16070239)
82  ������ 7852 MB (LBA 16082655)
83  ������ 7863 MB (LBA 16104927)
84  ������ 8895 MB (LBA 18218079)
85  ������ 8897 MB (LBA 18221279)
86  ������ 8907 MB (LBA 18243295)
87  ������ 8924 MB (LBA 18277855)
88  ������ 8952 MB (LBA 18334559)
89  ������ 8956 MB (LBA 18343775)
90  ������ 8966 MB (LBA 18362975)
91  ������ 8972 MB (LBA 18375519)
92  ������ 8974 MB (LBA 18378847)
93  ������ 8978 MB (LBA 18388191)
94  ������ 8980 MB (LBA 18391263)
95  ������ 8995 MB (LBA 18422879)
96  ������ 9004 MB (LBA 18441567)
97  ������ 9004 MB (LBA 18441695)
98  ������ 9034 MB (LBA 18501727)
99  ������ 9039 MB (LBA 18513887)
100  ������ 9041 MB (LBA 18517471)
101  ������ 9041 MB (LBA 18517599)
102  ������ 9050 MB (LBA 18535775)
103  ������ 9052 MB (LBA 18539103)
104  ������ 9059 MB (LBA 18554847)
105  ������ 9060 MB (LBA 18554975)
106  ������ 9060 MB (LBA 18555103)
107  ������ 9061 MB (LBA 18558175)
108  ������ 9061 MB (LBA 18558303)
109  ������ 9067 MB (LBA 18570591)
110  ������ 9069 MB (LBA 18573919)
111  ������ 9072 MB (LBA 18580575)
112  ������ 9074 MB (LBA 18583903)
113  ������ 9076 MB (LBA 18589535)
114  ������ 9076 MB (LBA 18589663)
115  ������ 9077 MB (LBA 18589791)
116  ������ 9078 MB (LBA 18592863)
117  ������ 9078 MB (LBA 18592991)
118  ������ 9087 MB (LBA 18611935)
119  ������ 9087 MB (LBA 18612063)
120  ������ 9089 MB (LBA 18615391)
121  ������ 9981 MB (LBA 20442463)
122  ������ 9988 MB (LBA 20455647)
123  ������ 9994 MB (LBA 20468063)
124  ������ 9997 MB (LBA 20474463)
125  ������ 10066 MB (LBA 20617183)
126  ������ 10077 MB (LBA 20639071)
127  ������ 10956 MB (LBA 22438751)
128  ������ 11053 MB (LBA 22637407)
129  ������ 11064 MB (LBA 22659295)
130  ������ 17248 MB (LBA 35324990)
131  ������ 17250 MB (LBA 35328062)
132  ������ 17251 MB (LBA 35331262)
133  ������ 17253 MB (LBA 35334462)
134  ������ 17254 MB (LBA 35337534)
135  ������ 17256 MB (LBA 35340606)
136  ������ 17256 MB (LBA 35340734)
137  ������ 17257 MB (LBA 35343806)
138  ������ 17259 MB (LBA 35346878)
139  ������ 17262 MB (LBA 35353150)
140  ������ 17263 MB (LBA 35356478)
141  ������ 17265 MB (LBA 35359422)
142  ������ 17265 MB (LBA 35359550)
143  ������ 17268 MB (LBA 35365694)
144  ������ 17269 MB (LBA 35368766)
145  ������ 17269 MB (LBA 35368894)
146  ������ 17271 MB (LBA 35371966)
147  ������ 17272 MB (LBA 35375038)
148  ������ 17274 MB (LBA 35378110)
149  ������ 17274 MB (LBA 35378238)
150  ������ 17288 MB (LBA 35406398)
151  ������ 17296 MB (LBA 35422526)
152  ������ 17296 MB (LBA 35423038)
153  ������ 17297 MB (LBA 35426110)
154  ������ 17299 MB (LBA 35428542)
155  ������ 17303 MB (LBA 35438014)
156  ������ 17305 MB (LBA 35441214)
157  ������ 17311 MB (LBA 35454270)
158  ������ 17311 MB (LBA 35454398)
159  ������ 17313 MB (LBA 35457470)
160  ������ 17314 MB (LBA 35460542)
161  ������ 17314 MB (LBA 35460670)
162  ������ 17316 MB (LBA 35463742)
163  ������ 17317 MB (LBA 35466558)
164  ������ 17317 MB (LBA 35466686)
165  ������ 17317 MB (LBA 35466814)
166  ������ 17319 MB (LBA 35469502)
167  ������ 17319 MB (LBA 35469630)
168  ������ 17319 MB (LBA 35469886)
169  ������ 17319 MB (LBA 35470014)
170  ������ 17320 MB (LBA 35473086)
171  ������ 17322 MB (LBA 35476158)
172  ������ 17322 MB (LBA 35476286)
173  ������ 17323 MB (LBA 35479358)
174  ������ 17325 MB (LBA 35482430)
175  ������ 17325 MB (LBA 35482558)
176  ������ 17326 MB (LBA 35485630)
177  ������ 17327 MB (LBA 35485758)
178  ������ 17328 MB (LBA 35488702)
179  ������ 17328 MB (LBA 35488830)
180  ������ 17328 MB (LBA 35488958)
181  ������ 17330 MB (LBA 35491902)
182  ������ 17331 MB (LBA 35494974)
183  ������ 17331 MB (LBA 35495102)
184  ������ 17333 MB (LBA 35498046)
185  ������ 17333 MB (LBA 35498174)
186  ������ 17333 MB (LBA 35498302)
187  ������ 17334 MB (LBA 35501246)
188  ������ 17334 MB (LBA 35501374)
189  ������ 17336 MB (LBA 35504318)
190  ������ 17336 MB (LBA 35504446)
191  ������ 17337 MB (LBA 35507518)
192  ������ 17337 MB (LBA 35507646)
193  ������ 17339 MB (LBA 35510462)
194  ������ 17339 MB (LBA 35510590)
195  ������ 17339 MB (LBA 35510718)
196  ������ 17339 MB (LBA 35510846)
197  ������ 17342 MB (LBA 35516862)
198  ������ 17342 MB (LBA 35516990)
199  ������ 17342 MB (LBA 35517118)
200  ������ 17342 MB (LBA 35517246)
201  ������ 17342 MB (LBA 35517374)
202  ������ 17343 MB (LBA 35520062)
203  ������ 17343 MB (LBA 35520190)
204  ������ 17343 MB (LBA 35520318)
205  ������ 17343 MB (LBA 35520446)
206  ������ 18410 MB (LBA 37704510)
207  ������ 18410 MB (LBA 37704638)
208  ������ 18410 MB (LBA 37704766)
209  ������ 18410 MB (LBA 37704894)
210  ������ 18410 MB (LBA 37705022)
211  ������ 18410 MB (LBA 37705150)
212  ������ 18410 MB (LBA 37705278)
213  ������ 18410 MB (LBA 37705406)
214  ������ 18410 MB (LBA 37705662)
215  ������ 18411 MB (LBA 37705790)
216  ������ 18411 MB (LBA 37707582)
217  ������ 18411 MB (LBA 37707710)
218  ������ 18412 MB (LBA 37707838)
219  ������ 18412 MB (LBA 37707966)
220  ������ 18412 MB (LBA 37708094)
221  ������ 18412 MB (LBA 37708222)
222  ������ 18412 MB (LBA 37708350)
223  ������ 18412 MB (LBA 37708478)
224  ������ 18412 MB (LBA 37708606)
225  ������ 18412 MB (LBA 37708734)
226  ������ 18412 MB (LBA 37708862)
227  ������ 18412 MB (LBA 37708990)
228  ������ 18413 MB (LBA 37710782)
229  ������ 18413 MB (LBA 37710910)
230  ������ 18413 MB (LBA 37711038)
231  ������ 18413 MB (LBA 37711166)
232  ������ 18413 MB (LBA 37711294)
233  ������ 18413 MB (LBA 37711422)
234  ������ 18413 MB (LBA 37711550)
235  ������ 18413 MB (LBA 37711678)
236  ������ 18414 MB (LBA 37712062)
237  ������ 18414 MB (LBA 37713854)
238  ������ 18415 MB (LBA 37713982)
239  ������ 18415 MB (LBA 37714110)
240  ������ 18415 MB (LBA 37714238)
241  ������ 18415 MB (LBA 37714366)
242  ������ 18415 MB (LBA 37714494)
243  ������ 18415 MB (LBA 37714622)
244  ������ 18415 MB (LBA 37714750)
245  ������ 18415 MB (LBA 37715006)
246  ������ 18416 MB (LBA 37717182)
247  ������ 18416 MB (LBA 37717310)
248  ������ 18416 MB (LBA 37717438)
249  ������ 18416 MB (LBA 37717566)
250  ������ 18416 MB (LBA 37717694)
251  ������ 18416 MB (LBA 37717822)
252  ������ 18416 MB (LBA 37717950)
253  ������ 18417 MB (LBA 37718206)
254  ������ 18417 MB (LBA 37718334)
255  ������ 18418 MB (LBA 37720382)
256  ������ 18418 MB (LBA 37720510)
257  ������ 18418 MB (LBA 37720638)
258  ������ 18418 MB (LBA 37720766)
259  ������ 18418 MB (LBA 37720894)
260  ������ 18418 MB (LBA 37721022)
261  ������ 18418 MB (LBA 37721406)
262  ������ 18419 MB (LBA 37723582)
263  ������ 18419 MB (LBA 37723710)
264  ������ 18419 MB (LBA 37723838)
265  ������ 18419 MB (LBA 37723966)
266  ������ 18419 MB (LBA 37724094)
267  ������ 18420 MB (LBA 37724222)
268  ������ 18420 MB (LBA 37724350)
269  ������ 18420 MB (LBA 37724478)
270  ������ 18421 MB (LBA 37726654)
271  ������ 18421 MB (LBA 37726782)
272  ������ 18421 MB (LBA 37726910)
273  ������ 18421 MB (LBA 37727038)
274  ������ 18421 MB (LBA 37727166)
275  ������ 18421 MB (LBA 37727294)
276  ������ 18421 MB (LBA 37727422)
277  ������ 18421 MB (LBA 37727550)
278  ������ 18421 MB (LBA 37727678)
279  ������ 18422 MB (LBA 37729726)
280  ������ 18422 MB (LBA 37729854)
281  ������ 18422 MB (LBA 37729982)
282  ������ 18422 MB (LBA 37730110)
283  ������ 18422 MB (LBA 37730238)
284  ������ 18423 MB (LBA 37730366)
285  ������ 18423 MB (LBA 37730494)
286  ������ 18423 MB (LBA 37730622)
287  ������ 18423 MB (LBA 37730750)
288  ������ 18423 MB (LBA 37730878)
289  ������ 18423 MB (LBA 37731006)
290  ������ 18424 MB (LBA 37732798)
291  ������ 18424 MB (LBA 37732926)
292  ������ 18424 MB (LBA 37733054)
293  ������ 18424 MB (LBA 37733182)
294  ������ 18424 MB (LBA 37733310)
295  ������ 18424 MB (LBA 37733438)
296  ������ 18424 MB (LBA 37733566)
297  ������ 18424 MB (LBA 37733694)
298  ������ 18424 MB (LBA 37733822)
299  ������ 18424 MB (LBA 37733950)
300  ������ 18424 MB (LBA 37734078)
301  ������ 18425 MB (LBA 37735998)
302  ������ 18425 MB (LBA 37736126)
303  ������ 18425 MB (LBA 37736254)
304  ������ 18425 MB (LBA 37736382)
305  ������ 18426 MB (LBA 37736510)
306  ������ 18426 MB (LBA 37736638)
307  ������ 18426 MB (LBA 37736766)
308  ������ 18426 MB (LBA 37736894)
309  ������ 18426 MB (LBA 37737022)
310  ������ 18426 MB (LBA 37737150)
311  ������ 18427 MB (LBA 37739070)
312  ������ 18427 MB (LBA 37739198)
313  ������ 18427 MB (LBA 37739326)
314  ������ 18427 MB (LBA 37739454)
315  ������ 18427 MB (LBA 37739582)
316  ������ 18427 MB (LBA 37739710)
317  ������ 18427 MB (LBA 37739838)
318  ������ 18427 MB (LBA 37739966)
319  ������ 18427 MB (LBA 37740094)
320  ������ 18427 MB (LBA 37740222)
321  ������ 18427 MB (LBA 37740350)
322  ������ 18428 MB (LBA 37742270)
323  ������ 18428 MB (LBA 37742398)
324  ������ 18428 MB (LBA 37742526)
325  ������ 18429 MB (LBA 37742654)
326  ������ 18429 MB (LBA 37742782)
327  ������ 18429 MB (LBA 37742910)
328  ������ 18429 MB (LBA 37743038)
329  ������ 18429 MB (LBA 37743166)
330  ������ 18429 MB (LBA 37743294)
331  ������ 18429 MB (LBA 37743422)
332  ������ 18430 MB (LBA 37745342)
333  ������ 18430 MB (LBA 37745470)
334  ������ 18430 MB (LBA 37745598)
335  ������ 18430 MB (LBA 37745726)
336  ������ 18430 MB (LBA 37745854)
337  ������ 18430 MB (LBA 37745982)
338  ������ 18430 MB (LBA 37746110)
339  ������ 18430 MB (LBA 37746238)
340  ������ 18430 MB (LBA 37746494)
341  ������ 18430 MB (LBA 37746622)
342  ������ 18431 MB (LBA 37748542)
343  ������ 18431 MB (LBA 37748670)
344  ������ 18432 MB (LBA 37748798)
345  ������ 18432 MB (LBA 37748926)
346  ������ 18432 MB (LBA 37749054)
347  ������ 18432 MB (LBA 37749182)
348  ������ 18432 MB (LBA 37749310)
349  ������ 18432 MB (LBA 37749438)
350  ������ 18432 MB (LBA 37749566)
351  ������ 18432 MB (LBA 37749694)
352  ������ 18433 MB (LBA 37751998)
353  ������ 18433 MB (LBA 37752126)
354  ������ 18433 MB (LBA 37752254)
355  ������ 18433 MB (LBA 37752382)
356  ������ 18433 MB (LBA 37752510)
357  ������ 18433 MB (LBA 37752638)
358  ������ 18433 MB (LBA 37752766)
359  ������ 18435 MB (LBA 37755070)
360  ������ 18435 MB (LBA 37755198)
361  ������ 18435 MB (LBA 37755326)
362  ������ 18435 MB (LBA 37755454)
363  ������ 18435 MB (LBA 37755582)
364  ������ 18435 MB (LBA 37755838)
365  ������ 18435 MB (LBA 37755966)
366  ������ 18436 MB (LBA 37758142)
367  ������ 18436 MB (LBA 37758270)
368  ������ 18436 MB (LBA 37758398)
369  ������ 18436 MB (LBA 37758526)
370  ������ 18436 MB (LBA 37758654)
371  ������ 18436 MB (LBA 37758782)
372  ������ 18436 MB (LBA 37758910)
373  ������ 18437 MB (LBA 37759038)
374  ������ 18438 MB (LBA 37761342)
375  ������ 18438 MB (LBA 37761470)
376  ������ 18438 MB (LBA 37761598)
377  ������ 18438 MB (LBA 37761726)
378  ������ 18438 MB (LBA 37761854)
379  ������ 18438 MB (LBA 37761982)
380  ������ 18438 MB (LBA 37762110)
381  ������ 18438 MB (LBA 37762238)
382  ������ 18438 MB (LBA 37762366)
383  ������ 18438 MB (LBA 37762494)
384  ������ 18439 MB (LBA 37764414)
385  ������ 18439 MB (LBA 37764542)
386  ������ 18439 MB (LBA 37764670)
387  ������ 18439 MB (LBA 37764798)
388  ������ 18439 MB (LBA 37764926)
389  ������ 18439 MB (LBA 37765054)
390  ������ 18440 MB (LBA 37765182)
391  ������ 18440 MB (LBA 37765310)
392  ������ 18440 MB (LBA 37765438)
393  ������ 18441 MB (LBA 37767614)
394  ������ 18441 MB (LBA 37767742)
395  ������ 18441 MB (LBA 37767870)
396  ������ 18441 MB (LBA 37767998)
397  ������ 18441 MB (LBA 37768126)
398  ������ 18441 MB (LBA 37768254)
399  ������ 18441 MB (LBA 37768382)
400  ������ 18442 MB (LBA 37770686)
401  ������ 18442 MB (LBA 37770814)
402  ������ 18442 MB (LBA 37770942)
403  ������ 18442 MB (LBA 37771070)
404  ������ 18442 MB (LBA 37771198)
405  ������ 18443 MB (LBA 37771326)
406  ������ 18443 MB (LBA 37771454)
407  ������ 18443 MB (LBA 37771582)
408  ������ 18443 MB (LBA 37771710)
409  ������ 18443 MB (LBA 37771838)
410  ������ 18444 MB (LBA 37773758)
411  ������ 18444 MB (LBA 37773886)
412  ������ 18444 MB (LBA 37774014)
413  ������ 18444 MB (LBA 37774142)
414  ������ 18444 MB (LBA 37774270)
415  ������ 18444 MB (LBA 37774398)
416  ������ 18444 MB (LBA 37774526)
417  ������ 18444 MB (LBA 37774654)
418  ������ 18444 MB (LBA 37774782)
419  ������ 18444 MB (LBA 37774910)
420  ������ 18445 MB (LBA 37776830)
421  ������ 18445 MB (LBA 37776958)
422  ������ 18445 MB (LBA 37777086)
423  ������ 18445 MB (LBA 37777214)
424  ������ 18445 MB (LBA 37777342)
425  ������ 18446 MB (LBA 37777470)
426  ������ 18446 MB (LBA 37777598)
427  ������ 18446 MB (LBA 37777726)
428  ������ 18446 MB (LBA 37777854)
429  ������ 18446 MB (LBA 37777982)
430  ������ 18446 MB (LBA 37778110)
431  ������ 18447 MB (LBA 37780030)
432  ������ 18447 MB (LBA 37780158)
433  ������ 18447 MB (LBA 37780286)
434  ������ 18447 MB (LBA 37780414)
435  ������ 18447 MB (LBA 37780542)
436  ������ 18447 MB (LBA 37780670)
437  ������ 18447 MB (LBA 37780798)
438  ������ 18447 MB (LBA 37780926)
439  ������ 18447 MB (LBA 37781054)
440  ������ 18447 MB (LBA 37781182)
441  ������ 18448 MB (LBA 37783486)
442  ������ 18449 MB (LBA 37783614)
443  ������ 18449 MB (LBA 37783742)
444  ������ 18449 MB (LBA 37783870)
445  ������ 18449 MB (LBA 37783998)
446  ������ 18449 MB (LBA 37784126)
447  ������ 18449 MB (LBA 37784254)
448  ������ 18450 MB (LBA 37786558)
449  ������ 18450 MB (LBA 37786686)
450  ������ 18450 MB (LBA 37786814)
451  ������ 18450 MB (LBA 37786942)
452  ������ 18450 MB (LBA 37787070)
453  ������ 18450 MB (LBA 37787198)
454  ������ 18450 MB (LBA 37787326)
455  ������ 18450 MB (LBA 37787454)
456  ������ 18451 MB (LBA 37789630)
457  ������ 18452 MB (LBA 37789758)
458  ������ 18452 MB (LBA 37789886)
459  ������ 18452 MB (LBA 37790014)
460  ������ 18452 MB (LBA 37790142)
461  ������ 18452 MB (LBA 37790270)
462  ������ 18452 MB (LBA 37790398)
463  ������ 18452 MB (LBA 37790526)
464  ������ 18453 MB (LBA 37792830)
465  ������ 18453 MB (LBA 37792958)
466  ������ 18453 MB (LBA 37793086)
467  ������ 18453 MB (LBA 37793214)
468  ������ 18453 MB (LBA 37793342)
469  ������ 18453 MB (LBA 37793470)
470  ������ 18453 MB (LBA 37793598)
471  ������ 18453 MB (LBA 37793726)
472  ������ 18454 MB (LBA 37793854)
473  ������ 18455 MB (LBA 37795902)
474  ������ 18455 MB (LBA 37796030)
475  ������ 18455 MB (LBA 37796158)
476  ������ 18455 MB (LBA 37796286)
477  ������ 18455 MB (LBA 37796414)
478  ������ 18455 MB (LBA 37796542)
479  ������ 18455 MB (LBA 37796670)
480  ������ 18455 MB (LBA 37796798)
481  ������ 18455 MB (LBA 37796926)
482  ������ 18455 MB (LBA 37797054)
483  ������ 18455 MB (LBA 37797182)
484  ������ 18456 MB (LBA 37798974)
485  ������ 18456 MB (LBA 37799102)
486  ������ 18456 MB (LBA 37799230)
487  ������ 18456 MB (LBA 37799358)
488  ������ 18456 MB (LBA 37799486)
489  ������ 18456 MB (LBA 37799614)
490  ������ 18456 MB (LBA 37799742)
491  ������ 18456 MB (LBA 37799870)
492  ������ 18457 MB (LBA 37799998)
493  ������ 18457 MB (LBA 37800126)
494  ������ 18457 MB (LBA 37800638)
495  ������ 18458 MB (LBA 37802174)
496  ������ 18458 MB (LBA 37802302)
497  ������ 18458 MB (LBA 37802430)
498  ������ 18458 MB (LBA 37802558)
499  ������ 18458 MB (LBA 37802686)
500  ������ 18458 MB (LBA 37802814)
501  ������ 18458 MB (LBA 37802942)
502  ������ 18458 MB (LBA 37803070)
503  ������ 18458 MB (LBA 37803326)
504  ������ 18459 MB (LBA 37804734)
505  ������ 18459 MB (LBA 37805246)
506  ������ 18459 MB (LBA 37805374)
507  ������ 18459 MB (LBA 37805502)
508  ������ 18459 MB (LBA 37805630)
509  ������ 18459 MB (LBA 37805758)
510  ������ 18459 MB (LBA 37805886)
511  ������ 18459 MB (LBA 37806014)
512  ������ 18460 MB (LBA 37806142)
513  ������ 18460 MB (LBA 37806270)
514  ������ 18460 MB (LBA 37806398)
515  ������ 18461 MB (LBA 37808318)
516  ������ 18461 MB (LBA 37808446)
517  ������ 18461 MB (LBA 37808574)
518  ������ 18461 MB (LBA 37808702)
519  ������ 18461 MB (LBA 37808830)
520  ������ 18461 MB (LBA 37808958)
521  ������ 18461 MB (LBA 37809086)
522  ������ 18461 MB (LBA 37809214)
523  ������ 18461 MB (LBA 37809342)
524  ������ 18461 MB (LBA 37809470)
525  ������ 18461 MB (LBA 37809598)
526  ������ 18462 MB (LBA 37811518)
527  ������ 18462 MB (LBA 37811646)
528  ������ 18462 MB (LBA 37811774)
529  ������ 18462 MB (LBA 37811902)
530  ������ 18462 MB (LBA 37812030)
531  ������ 18462 MB (LBA 37812158)
532  ������ 18463 MB (LBA 37812286)
533  ������ 18463 MB (LBA 37812414)
534  ������ 18463 MB (LBA 37812670)
535  ������ 18464 MB (LBA 37814846)
536  ������ 18464 MB (LBA 37814974)
537  ������ 18464 MB (LBA 37815102)
538  ������ 18464 MB (LBA 37815230)
539  ������ 18464 MB (LBA 37815358)
540  ������ 18464 MB (LBA 37815486)
541  ������ 18464 MB (LBA 37815614)
542  ������ 18464 MB (LBA 37815742)
543  ������ 18464 MB (LBA 37815870)
544  ������ 18465 MB (LBA 37818046)
545  ������ 18465 MB (LBA 37818174)
546  ������ 18465 MB (LBA 37818302)
547  ������ 18466 MB (LBA 37818430)
548  ������ 18466 MB (LBA 37818558)
549  ������ 18466 MB (LBA 37818686)
550  ������ 18466 MB (LBA 37818814)
551  ������ 18466 MB (LBA 37818942)
552  ������ 18467 MB (LBA 37821246)
553  ������ 18467 MB (LBA 37821374)
554  ������ 18467 MB (LBA 37821502)
555  ������ 18467 MB (LBA 37821630)
556  ������ 18467 MB (LBA 37821758)
557  ������ 18467 MB (LBA 37821886)
558  ������ 18467 MB (LBA 37822014)
559  ������ 18468 MB (LBA 37824318)
560  ������ 18468 MB (LBA 37824446)
561  ������ 18469 MB (LBA 37824574)
562  ������ 18469 MB (LBA 37824702)
563  ������ 18469 MB (LBA 37824830)
564  ������ 18469 MB (LBA 37824958)
565  ������ 18469 MB (LBA 37825086)
566  ������ 18469 MB (LBA 37825214)
