CREATE TABLE `borrowers` (
 `id` int(30) NOT NULL,
 `firstname` varchar(100) NOT NULL,
 `middlename` varchar(100) NOT NULL,
 `lastname` varchar(100) NOT NULL,
 `contact_no` varchar(30) NOT NULL,
 `address` text NOT NULL,
 `email` varchar(50) NOT NULL,
 `tax_id` varchar(50) NOT NULL,
 `date_created` int(11) NOT NULL
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
 CREATE TABLE `loan_list` (
 `id` int(30) NOT NULL,
 `ref_no` varchar(50) NOT NULL,
 `loan_type_id` int(30) NOT NULL,
 `borrower_id` int(30) NOT NULL,
 `purpose` text NOT NULL,
 `amount` double NOT NULL,
 `plan_id` int(30) NOT NULL,
 `status` tinyint(1) NOT NULL DEFAULT 0 COMMENT '0= request,
 1=confrimed,2=released,3=complteted,4=denied\r\n', 
 `date_released` datetime NOT NULL,
`date_created` datetime NOT NULL DEFAULT current_timestamp () ON UPDATE 
 current_timestamp() 
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
ONLINE LOAN MANAGEMENT SYSTEM 1BI21CS412
17
Department of CS&E, BIT 2022-23 
 
 CREATE TABLE `loan_plan` (
 `id` int(30) NOT NULL,
 `months` int(11) NOT NULL,
 `interest_percentage` float NOT NULL,
 `penalty_rate` int(11) NOT NULL
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
 CREATE TABLE `loan_schedules` (
 `id` int(30) NOT NULL,
 `loan_id` int(30) NOT NULL,
 `date_due` date NOT NULL
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
 CREATE TABLE `loan_types` (
 `id` int(30) NOT NULL,
 `type_name` text NOT NULL,
 `description` text NOT NULL
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
 CREATE TABLE `payments` (
 `id` int(30) NOT NULL,
 `loan_id` int(30) NOT NULL,
 `payee` text NOT NULL,
 `amount` float NOT NULL DEFAULT 0,
 `penalty_amount` float NOT NULL DEFAULT 0,
`overdue` tinyint(1) NOT NULL DEFAULT 0 COMMENT '0=no , 1 = yes',
 `date_created` datetime NOT NULL DEFAULT current_timestamp()
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
ONLINE LOAN MANAGEMENT SYSTEM 1BI21CS412
18
Department of CS&E, BIT 2022-23 
 CREATE TABLE `users` (
 `id` int(30) NOT NULL,
 `doctor_id` int(30) NOT NULL,
 `name` varchar(200) NOT NULL,
 `address` text NOT NULL,
 `contact` text NOT NULL,
 `username` varchar(100) NOT NULL,
 `password` varchar(200) NOT NULL,
 `type` tinyint(1) NOT NULL DEFAULT 2 COMMENT '1=admin , 2 = staff'
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
5.2 PHP CODE
5.2.1 Borrowers.php
<?php include 'db_connect.php' ?> 
<div class="container-fluid"> 
<div class="col-lg-12"> 
<div class="card"> 
<div class="card-header"> 
<large class="card-title"> 
<b>Borrower List</b> 
</large> 
<button class="btn btn-primary btn-block col-md-2 float-right" type="button" 
id="new_borrower"><i class="fa fa-plus"></i> New 
Borrower</button> </div> 
<div class="card-body"> 
<table class="table table-bordered" id="borrower list"> <colgroup> 
<col width="10%"> 
<col width="35%"> 
<col width="30%"> 
<col width="15%"> 
<col width="10%"> 
</colgroup> 
<thead> 
ONLINE LOAN MANAGEMENT SYSTEM 1BI21CS412
19
Department of CS&E, BIT 2022-23 
<tr> 
<th class="text-center">#</th> 
<th class="text-center">Borrower</th> 
<th class="text-center">Current Loan</th> 
<th class="text-center">Next Payment 
Schedule</th> <th class="text-center">Action</th> 
</tr> 
</thead> 
<tbody> 
<?php 
$i = 1; 
$qry = $conn->query("SELECT * FROM borrowers order by id desc"); while($row 
= $qry->fetch_assoc()): 
?> 
<tr> 
<td class="text-center"><?php echo $i++ 
?></td> <td> 
<p>Name :<b><?php echo ucwords($row['lastname'].", 
".$row['firstname'].' '.$row['middlename']) ?></b></p> 
<p><small>Address :<b><?php echo $row['address'] ?></small></b></p> 
<p><small>Contact # :<b><?php echo $row['contact_no'] ?></small></b></p> 
<p><small>Email :<b><?php echo $row['email'] ?></small></b></p> 
<p><small>Tax ID :<b><?php echo $row['tax_id'] ?></small></b></p> 
</td> 
<td class="">None</td> 
<td class="">N/A</td> 
<td class="text-center"> 
<button class="btn btn-outline-primary btn-sm edit_borrower" type="button" data
id="<?php echo $row['id'] ?>"><i class="fa fa-edit"></i></button> 
<button class="btn btn-outline-danger btn-sm delete_borrower" type="button" 
dataid="<?php echo $row['id'] ?>"><i class="fa fa-trash"></i></button> </td> </tr> 
<?php endwhile; ?> 
</tbody> 
</table> 
</div> 
</div> 
</div> 
ONLINE LOAN MANAGEMENT SYSTEM 1BI21CS412
20
Department of CS&E, BIT 2022-23 
</div> <style> td p { 
margin:unset; 
} 
td img { 
width: 8vw; 
height: 12vh; 
} 
td{ 
vertical-align: middle !important; 
} 
</style> 
<script> 
$('#borrower-list').dataTable() 
$('#new_borrower').click(function(){ uni_modal("New 
borrower","manage_borrower.php",'mid-large') 
}) 
$('.edit_borrower').click(function(){ uni_modal("Edit
borrower","manage_borrower.php?id="+$(this).attr('data-id'),'mid-large') 
}) 
$('.delete_borrower').click(function(){ 
conf("Are you sure to delete this borrower?","delete_borrower",[$(this).attr('dataid')]) 
}) 
function delete_borrower($id){ start_load()
$.ajax({ url:'ajax.php?action=delete_borrower', 
method:'POST', data:{id:$id}, success:function(resp){ 
if(resp==1){ 
alert_toast("borrower successfully deleted",'success') 
setTimeout(function(){ 
location.reload() 
},1500) 
} 
} 
}) 
} 
</script> 
 5.2.2 Loan Type.php
ONLINE LOAN MANAGEMENT SYSTEM 1BI21CS412
21
Department of CS&E, BIT 2022-23 
 <?php include 'db_connect.php' ?> 
<div class="container-fluid"> 
<div class="col-lg-12"> 
<div class="card"> 
<div class="card-header"> 
<large class="card-title"> 
<b>Borrower List</b> </large> 
<button class="btn btn-primary btn-block col-md-2 float-right" type="button" 
id="new_borrower"><i class="fa fa-plus"></i> New Borrower</button> </div> 
<div class="card-body"> 
<table class="table table-bordered" id="borrower list"> <colgroup> 
<col width="10%"> 
<col width="35%"> 
<col width="30%"> 
<col width="15%"> 
<col width="10%"> 
</colgroup> 
<thead> 
<tr> 
<th class="text-center">#</th> 
<th class="text-center">Borrower</th> 
<th class="text-center">Current Loan</th> 
<th class="text-center">Next Payment 
Schedule</th> <th class="text-center">Action</th> 
</tr> 
</thead> 
 <tbody> 
<?php 
$i = 1; 
$qry = $conn->query("SELECT * FROM borrowers order by id desc"); while($row = 
$qry->fetch_assoc()): 
ONLINE LOAN MANAGEMENT SYSTEM 1BI21CS412
22
Department of CS&E, BIT 2022-23 
?> 
<tr>
<td class="text-center"><?php echo $i++ ?></td> 
<td> 
<p>Name :<b><?php echo ucwords($row['lastname'].", ".$row['firstname'].' 
'.$row['middlename']) ?></b></p> 
<p><small>Address :<b><?php echo $row['address'] ?></small></b></p> 
<p><small>Contact # :<b><?php echo $row['contact_no'] ?></small></b></p> 
<p><small>Email :<b><?php echo $row['email'] ?></small></b></p> 
<p><small>Tax ID :<b><?php echo $row['tax_id'] ?></small></b></p> 
</td> 
<td class="">None</td> 
<td class="">N/A</td> 
<td class="text-center"> 
<button class="btn btn-outline-primary btn-sm edit_borrower" type="button" dataid="<?php echo $row['id'] ?>"><i class="fa fa-edit"></i></button> 
<button class="btn btn-outline-danger btn-sm delete_borrower" type="button" dataid="<?php echo $row['id'] ?>"><i class="fa fa-trash"></i></button> </td> 
</tr>
<?php endwhile; ?> 
</tbody> 
</table> 
</div> 
</div> 
</div> 
</div> 
 <style> td p { margin:unset; 
} 
td img { width: 8vw; 
height: 12vh; 
} 
td{ 
ONLINE LOAN MANAGEMENT SYSTEM 1BI21CS412
23
Department of CS&E, BIT 2022-23 
vertical-align: middle !important; 
} 
</style> 
<script> 
$('#borrower-list').dataTable() 
$('#new_borrower').click(function(){ 
uni_modal("New borrower","manage_borrower.php",'mid-large') 
}) 
$('.edit_borrower').click(function(){ 
uni_modal("Edit borrower","manage_borrower.php?id="+$(this).attr('data-id'),'mid-large') 
}) 
$('.delete_borrower').click(function(){ 
_conf("Are you sure to delete this borrower?","delete_borrower",[$(this).attr('data-id')]) 
}) 
function delete_borrower($id){ 
start_load() $.ajax({ 
url:'ajax.php?action=delete_borrower', 
method:'POST', data:{id:$id}, success:function(resp){ if(resp==1){ 
alert_toast("borrower successfully deleted",'success') 
setTimeout(function(){ 
location.reload() 
},1500)
} 
} 
}) 
} 
</script>