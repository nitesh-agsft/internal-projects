class CustomerController < ApplicationController
    layout 'standard' 
    
    def list
            
    end
   
    def show
         
    end
   
    def new
        @customer = Customer.new
        #@customlist = Customer.all
        if params[:account_no].blank?
            puts "blank"
            @accpt = "null"
            @fetchedaccount = "null"
        else
            puts "got values"
            @lastname = params[:lastname]
            @firstname = params[:firstname]
            @middlename = params[:middlename]
            @headofhouse = params[:headofhouse]
            @account_no = params[:account_no]   
            @fetchedaccount = Customer.where(account_no: @account_no)
            puts "new value",@fetchedaccount,@account_no
        end            
            puts @lastname, @firstname, @headofhouse, @account_no        
    end
    
    
    def paramac
        params.require(:customers).permit(:account_no)
    end
        
    def create
        @findaccn = Account.where(paramac)
        @findaccn.each do |t|
            @ln = t.lastname.capitalize
            @mn = t.middlename.capitalize
            @fn = t.firstname.capitalize
            @hh = t.headofhouse.capitalize
            @an = t.account_no
        end
        redirect_to :action => 'new', :account_no => @an, :lastname => @ln, :firstname => @fn, :headofhouse => @hh, :middlename => @mn
    end
           
    def edit
          
    end
   
    def update
        
    end
    
    def delete
        Customer.find(params[:id]).destroy
        redirect_to :action => "new"
    end
    
    def add
        
    end
    def insert
        @accninsert = Customer.new(fetchaccount) 
        if @accninsert.save
            flash[:error]="Successfully added a plan"
            redirect_to :action => 'new', :controller => 'account'
        else
            flash[:error]="Sorry try again later"
            render :action =>'new'
        end
    end
    
    
    def fetchaccount
        params.require(:customers).permit(:account_no, :plans, :planname, :paytype, :plantype, :accountingmethod, :hohpresent, :headofhouseaccn)
    end  
end
