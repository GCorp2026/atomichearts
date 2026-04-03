// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract ItemRegistry {
    struct Item {
        uint256 tokenId;
        address owner;
        string itemType;      // "weapon" or "armor"
        string itemClass;      // "Primary_AR", "Helmet", etc
        uint256 seed;
        string name;
        string rarity;
        uint256 createdAt;
        uint256 lastPrice;
    }
    
    mapping(uint256 => Item) public items;
    uint256 public itemCount;
    
    event ItemCreated(uint256 tokenId, address owner, string name);
    event ItemTransferred(uint256 tokenId, address from, address to, uint256 price);
    
    function createItem(
        string memory itemType,
        string memory itemClass,
        uint256 seed,
        string memory name,
        string memory rarity
    ) public returns (uint256) {
        itemCount++;
        uint256 tokenId = uint256(keccak256(abi.encodePacked(seed, itemType, block.timestamp)));
        
        items[tokenId] = Item({
            tokenId: tokenId,
            owner: msg.sender,
            itemType: itemType,
            itemClass: itemClass,
            seed: seed,
            name: name,
            rarity: rarity,
            createdAt: block.timestamp,
            lastPrice: 0
        });
        
        emit ItemCreated(tokenId, msg.sender, name);
        return tokenId;
    }
    
    function getItem(uint256 tokenId) public view returns (Item memory) {
        return items[tokenId];
    }
    
    function getOwnerItems(address owner) public view returns (uint256[] memory) {
        uint256[] memory result = new uint256[](itemCount);
        uint256 count = 0;
        for (uint256 i = 1; i <= itemCount; i++) {
            if (items[i].owner == owner) {
                result[count++] = items[i].tokenId;
            }
        }
        return result;
    }
}
