Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
    
    resources :accounts
    get 'account/list'
    get 'account/show'
    get 'account/new'
    post 'account/create'
    patch 'account/update'
    get 'account/edit'
    get 'account/delete'
    get 'account/autoassign'
    resources :accounts
    get 'customer/list'
    get 'customer/show'
    get 'customer/new'
    post 'customer/add'
    post 'customer/create'
    patch 'customer/update'
    get 'customer/edit'
    get 'customer/delete'
    get 'customer/autoassign'
    get 'planlist/new'
    get 'planlist/edit'
    get 'planlist/delete'
    get 'planlist/list'
    post 'planlist/create'
    patch 'planlist/update'
    post 'customer/insert'
    
    
    
end
