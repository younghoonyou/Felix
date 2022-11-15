import React, { useState } from 'react';

const Balance = (props) => {
  const { balanceFromBackend } = props;
  const [username, setUsername] = useState('');

  const handleBalance = async () => {
    //do something
  };
  return (
    <div className='balance-container'>
      <div className='balance-username-container'>
        <label className='balance-username-title'>USER NAME</label>
        <input
          className='balance-username'
          value={username}
          onChange={(e) => setUsername(e.target.value)}
        />
      </div>
      <div>
        <div className='balance-balance-container'>
          <label className='balance-balance-title'>BALANCE</label>
          <div className='balance-balance'>${balanceFromBackend}</div>
        </div>
      </div>
      <button className='balance-refresh-button' onClick={handleBalance}>
        Balance
      </button>
    </div>
  );
};

export default Balance;
