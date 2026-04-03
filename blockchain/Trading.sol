// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "./ItemRegistry.sol";

contract Trading {
    ItemRegistry public registry;
    uint256 public commissionRate = 30; // 30%
    address public treasury;
    
    event ItemSold(uint256 tokenId, address seller, address buyer, uint256 price, uint256 commission);
    
    constructor(address _registry, address _treasury) {
        registry = ItemRegistry(_registry);
        treasury = _treasury;
    }
    
    function setCommissionRate(uint256 _rate) public {
        require(msg.sender == treasury);
        commissionRate = _rate;
    }
    
    function buyItem(uint256 tokenId) public payable {
        ItemRegistry.Item memory item = registry.getItem(tokenId);
        require(item.owner != msg.sender, "Cannot buy own item");
        
        uint256 price = item.lastPrice;
        require(msg.value >= price, "Insufficient payment");
        
        uint256 commission = (price * commissionRate) / 100;
        uint256 sellerPayout = price - commission;
        
        // Transfer item ownership (simplified - real implementation would call registry)
        address seller = item.owner;
        
        // Pay seller
        payable(seller).transfer(sellerPayout);
        // Pay commission to treasury
        payable(treasury).transfer(commission);
        
        emit ItemSold(tokenId, seller, msg.sender, price, commission);
    }
    
    function listItem(uint256 tokenId, uint256 price) public {
        // Implementation would update item.lastPrice
    }
}
