## Network Problems
* `traceroute`, `ping`, `proxy server`

## Webpage
* Reduce redirects, reduce HTTP request-response cycle 
* Reducing the number of webpage components , in turn reduces the number of HTTP requests required to render the page. Combine CSS/Javascript/.. files
* Use a Content Delivery Network : Deploying your content across multiple, geographically dispersed servers will make your pages load faster from the user's perspective.CDNs help offload traffic spikes and are often economical ways to scale parts of a site’s traffic.This optimization could be based on such things as the fewest network hops, highest availability, or fewest requests.This layer provides the benefit of faster delivery, typically very high availability, and less traffic on your site’s servers.
* Put Stylesheets at the Top : This is because putting stylesheets in the HEAD allows the page to render progressively.It is recommended because when you have the CSS declared before <body> starts, your styles has actually loaded already. So very quickly users see something appear on their screen (e.g. background colors). If not, users see blank screen for some time before the CSS reaches the user.
* Put Scripts at the Bottom : By placing the JS at the bottom of your page before the closing </body> tag, you are allowing the HTML to be parsed prior to loading the javascript. This gives the effect of faster page load times.
* Make JavaScript and CSS External : Using external files in the real world generally produces faster pages because the JavaScript and CSS files are cached by the browser. JavaScript and CSS that are inlined in HTML documents get downloaded every time the HTML document is requested. This reduces the number of HTTP requests that are needed, but increases the size of the HTML document. On the other hand, if the JavaScript and CSS are in external files cached by the browser, the size of the HTML document is reduced without increasing the number of HTTP requests.
* Reduce DNS Lookups : DNS has a cost. It typically takes 20-120 milliseconds for DNS to lookup the IP address for a given hostname. The browser can't download anything from this hostname until the DNS lookup is completed.Reducing the number of unique hostnames reduces the number of DNS lookups.
* Minify JavaScript and CSS : Minification is the practice of removing unnecessary characters from code to reduce its size thereby improving load times. When code is minified all comments are removed, as well as unneeded white space characters (space, newline, and tab). 

## Service
* No/Poor Load Distribution : Poor load distribution can cause slow response times by incorrectly assigning new site visitors to bogged-down servers instead of others with cycles to spare.
* Lack of caching or inefficient caching : Caching-related issues that can significantly affect Web services performance include failure to use caching for Web methods, caching too much data, caching inappropriate data, and using inappropriate expiration settings.It’s important to optimize your cache settings carefully, so that you maintain a good “hit ratio” without exhausting all the memory.
* It is bad to  create threads on a per-request basis. By maintaining a pool of threads, the model increases performance and avoids latency in execution due to frequent creation and destruction of threads for short-lived tasks.
* If the thread pool is sized too small then your requests are going to wait but if the thread pool is sized too large then too many threads are going to execute concurrently and take all of the machine’s processing resources. When there are too many threads and the machine spends too much time context switching between threads, the threads will be “starved” of CPU cycles and will take longer to complete. ```Small thread pool => thread pool utilization near 100% => execution queue increase => CPU underutilized```, ```Large thread pool => CPU utilization high```. The key is to look at two metrics: 
  * Thread pool utilization
  * CPU utilization
* Enable compression : Compression reduces response times by reducing the size of the HTTP response. Gzip is the most popular and effective compression method at this time.


## Database
* Indexing : Make sure appropriate indexes is built for fast access. Analyze the frequently-used queries and examine the query plan when it is executed (e.g. use "explain" for MySQL). Check whether appropriate index exist and being used.
* Data De-normalization : Table join is an expensive operation and should be reduced as much as possible. One technique is to de-normalize the data such that certain information is repeated in different tables.
* DB Replication : For typical web application where the read/write ratio is high, it will be useful to maintain multiple read-only replicas so that read access workload can be spread across. For example, in a 1 master/N slaves case, all update goes to master DB which send a change log to the replicas. However, there will be a time lag for replication.
* Transaction Processing : Avoid mixing OLAP (query intensive) and OLTP (update intensive) operations within the same DB. In the OLTP system, avoid using long running database transaction and choose the isolation level appropriately. 
* The database tables should be properly normalized
* Proper caching is not in place : Many applications make use of temporary caches on the application server to store the reference data or frequently accessed data as memory is less of an issue than the time with new generation servers.
* Number of rows in the table too large: If the table itself has too much of data then the queries will take time to execute. Partitioning a table into multiple tables is recommended in these situations.
* Connections are not being pooled : If connections are not pooled then the each time a new connection is requested for a request to database. Maintaining a connection pool is much better than creating and destroying the connection for executing every SQL query. Connections not closed/returned to pool in case of exceptions: When an exception occurs while performing database operations, it ought to be caught. 
